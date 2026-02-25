#include <stdio.h>

#define MAX 100

int main() {
    int n, process[MAX];
    int active[MAX];
    int initiator;
    int i, current, next;
    int msg_id;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter process IDs:\n");
    for(i = 0; i < n; i++) {
        scanf("%d", &process[i]);
        active[i] = 1;   // 1 means process is alive
    }

    printf("\nEnter index of process initiating election (0 to %d): ", n-1);
    scanf("%d", &initiator);

    if(active[initiator] == 0) {
        printf("Initiator process is not active.\n");
        return 0;
    }

    printf("\nElection initiated by Process %d\n", process[initiator]);

    msg_id = process[initiator];
    current = initiator;

    // Ring Election
    do {
        next = (current + 1) % n;

        if(active[next]) {
            printf("Process %d sends message (%d) to Process %d\n",
                   process[current], msg_id, process[next]);

            if(process[next] > msg_id) {
                msg_id = process[next];
            }
        }

        current = next;

    } while(current != initiator);

    printf("\nProcess %d becomes the COORDINATOR\n", msg_id);

    // Coordinator Announcement
    printf("\nCoordinator message circulating...\n");

    current = initiator;
    do {
        next = (current + 1) % n;

        if(active[next]) {
            printf("Process %d informs Process %d that Process %d is Coordinator\n",
                   process[current], process[next], msg_id);
        }

        current = next;

    } while(current != initiator);

    printf("\nElection completed successfully.\n");

    return 0;
}