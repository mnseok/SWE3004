#include "user.h"

int main(int argc, char *argv[]) {
    int pid = getpid();  // 현재 프로세스 ID 가져오기

    printf("===== nice Test =====\n");

    int nice = getnice(pid);  // 현재 프로세스의 nice 값을 가져오기

    printf("Process %d has nice value: %d\n", pid, nice);

    setnice(pid, 10);  // 현재 프로세스의 nice 값을 10으로 설정

    nice = getnice(pid);  // 변경된 nice 값을 가져오기
    printf("Process %d has nice value: %d\n", pid, nice);

    printf("===== ps Test =====\n");

    ps(pid);  // 현재 프로세스의 상태 출력
  
    ps(0);  // 전체 프로세스의 상태 출력

    printf("===== meminfo Test =====\n");

    uint64 mem = meminfo();  // 메모리 정보 가져오기
    printf("Total memory: %ld\n", mem);

    printf("===== waitpid Test =====\n");

    int wpid = fork();  // 자식 프로세스 생성

    if (wpid < 0) {
        printf("Fork failed\n");
        exit(1);
    }
    
    if (wpid == 0) {
        sleep(100);  // 자식 프로세스가 500ms 동안 sleep
        printf("Child process %d exiting...\n", getpid());
        exit(0);
    } else {
        int status = waitpid(wpid);  // 자식 프로세스가 종료될 때까지 대기
        if (status == -1) {
            printf("Error: waitpid failed for %d\n", wpid);
        } else {
            printf("Child process %d exited with status %d\n", wpid, status);
        }
    }

    printf("===== ALL TESTS PASSED =====\n");

    exit(0);
}
