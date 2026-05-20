#include <stdio.h>
#include <string.h>

#define MAX 52

typedef struct {
    int x, y;
    char dir;
} Robot;

int maxX, maxY;
int scent[MAX][MAX];

char turn_left(char dir) {
    switch (dir) {
    case 'N': return 'W';
    case 'W': return 'S';
    case 'S': return 'E';
    case 'E': return 'N';
    }
    return dir;
}

char turn_right(char dir) {
    switch (dir) {
    case 'N': return 'E';
    case 'E': return 'S';
    case 'S': return 'W';
    case 'W': return 'N';
    }
    return dir;
}

void move_forward(int* x, int* y, char dir) {
    switch (dir) {
    case 'N': (*y)++; break;
    case 'E': (*x)++; break;
    case 'S': (*y)--; break;
    case 'W': (*x)--; break;
    }
}

int is_off_grid(int x, int y) {
    return x < 0 || x > maxX || y < 0 || y > maxY;
}

int main() {
    FILE* in;
    errno_t err = fopen_s(&in, "robot.in", "r");
    if (err != 0 || in == NULL) {
        printf("無法打開檔案 robot.in\n");
        return 1;
    }

    int test_cases;
    fscanf_s(in, "%d", &test_cases);

    fscanf_s(in, "%d %d", &maxX, &maxY);

    memset(scent, 0, sizeof(scent));

    for (int t = 0; t < test_cases; t++) {
        Robot robot;
        char commands[110];
        char dir;
        fscanf_s(in, "%d %d %c", &robot.x, &robot.y, &dir, 1);
        robot.dir = dir;
        fscanf_s(in, "%s", commands, (unsigned)sizeof(commands));

        int lost = 0;

        for (int i = 0; commands[i] != '\0'; i++) {
            if (commands[i] == 'L') {
                robot.dir = turn_left(robot.dir);
            }
            else if (commands[i] == 'R') {
                robot.dir = turn_right(robot.dir);
            }
            else if (commands[i] == 'F') {
                int nextX = robot.x, nextY = robot.y;
                move_forward(&nextX, &nextY, robot.dir);

                if (is_off_grid(nextX, nextY)) {
                    if (!scent[robot.x][robot.y]) {
                        scent[robot.x][robot.y] = 1;
                        lost = 1;
                        break;
                    }
                }
                else {
                    robot.x = nextX;
                    robot.y = nextY;
                }
            }
        }

        printf("%d %d %c", robot.x, robot.y, robot.dir);
        if (lost) {
            printf(" LOST");
        }
        printf("\n");
    }

    fclose(in);
    return 0;
}
