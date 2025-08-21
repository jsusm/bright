#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int get_current_brightness() {
  int curr_bright = -1;
  pid_t pid;

  char buff[6];
  ssize_t bytesReaded;

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    printf("Error: opening the pipe\n");
    return -1;
  }

  pid = fork();

  if (pid == 0) {                   // child process
    close(pipefd[0]);               // close read end
    dup2(pipefd[1], STDOUT_FILENO); // redirect stdout to pipe write end
    close(pipefd[1]);               // close original write end

    execlp("brightnessctl", "brightnessctl", "g", NULL);
    printf("Error: The command doesn't execute properly\n");
    return -1;
  } else {
    close(pipefd[1]); // close white end

    if ((bytesReaded = read(pipefd[0], buff, sizeof(buff) - 1)) > 0) {
      buff[bytesReaded] = '\0';
      curr_bright = atoi(buff);
    } else {
      printf("Error: Do not Read anything from brightnessctl command\n");
    }

    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    return curr_bright;
  }
}

int get_max_brightness() {
  int max_bright = -1;
  pid_t pid;

  char buff[6];
  ssize_t bytesReaded;

  int pipefd[2];
  if (pipe(pipefd) == -1) {
    printf("Error: opening the pipe\n");
    return -1;
  }

  pid = fork();

  if (pid == 0) {                   // child process
    close(pipefd[0]);               // close read end
    dup2(pipefd[1], STDOUT_FILENO); // redirect stdout to pipe write end
    close(pipefd[1]);               // close original write end

    execlp("brightnessctl", "brightnessctl", "m", NULL);
    printf("Error: The command doesn't execute properly\n");
    return -1;
  } else {
    close(pipefd[1]); // close white end

    if ((bytesReaded = read(pipefd[0], buff, sizeof(buff) - 1)) > 0) {
      buff[bytesReaded] = '\0';
      max_bright = atoi(buff);
    } else {
      printf("Error: Do not Read anything from brightnessctl command\n");
    }

    close(pipefd[0]);
    waitpid(pid, NULL, 0);
    return max_bright;
  }
}

int set_brightness(int brightness) {
  pid_t pid;

  pid = fork();

  if (pid == 0) {
    char brightness_arg[6];
    sprintf(brightness_arg, "%d", brightness);
    execlp("brightnessctl", "brightnessctl", "s", brightness_arg, NULL);
    printf("Error: The command doesn't execute properly\n");
    return -1;
  } else {
    waitpid(pid, NULL, 0);
    return 1;
  }
}

int compute_increase_brightness(int curr, int max) {
  if (curr == 0) {
    return 1;
  }
  if (curr * 1.2 > max) {
    return max;
  } else {
    return curr * 1.2;
  }
}
int compute_decrease_brightness(int curr, int max) { return curr * 0.8; }

void print_help() {
  puts("Usage:");
  puts("screli d \t\t\t Decrease the brightness by 20% of the current "
       "brightness");
  puts("screli i \t\t\t Increase the brightness by 20% of the current "
       "brightness");
  puts("screli\t\t\t Show the current brightness");
}

int main(int argc, char *argv[]) {
  int curr_bright = get_current_brightness();
  if (curr_bright < 0) {
    printf("Error: reading the current brightness\n");
  }
  int max_bright = get_max_brightness();
  if (max_bright < 0) {
    printf("Error: reading the max brightness\n");
  }

  if (argc == 1) {
    printf("%d ~ %d%%\n", curr_bright, (curr_bright * 100) / max_bright);
    return 0;
  }
  if (argc == 2) {
    int newBrighness;
    if (strcmp(argv[1], "i") == 0) {
      newBrighness = compute_increase_brightness(curr_bright, max_bright);
      set_brightness(newBrighness);
      printf("%d ~ %d%%\n", newBrighness, (newBrighness * 100) / max_bright);
    } else if (strcmp(argv[1], "d") == 0) {
      newBrighness = compute_decrease_brightness(curr_bright, max_bright);
      set_brightness(newBrighness);
      printf("%d ~ %d%%\n", newBrighness, (newBrighness * 100) / max_bright);
    } else {
      print_help();
    }
  } else {
    print_help();
  }
  return 0;
}
