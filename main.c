#include <stdio.h>
#define max 100

typedef struct process{
    int p_id;
    int priority;
    int brust_time;
    int remaning_time;
    int waiting_time;
    int turnaround_time
}process;


process q0[max], q1[max] ,q2[max], q3[max];

int size_q0=0,size_q1=0,size_q2=0,size_q3=0;
int totalTime = 0;


void enqueue(process *q, int *size, process p){
    //printf("dunna\n");
    q[*size]=p;
    (*size)++;
}

process dequeue(process*q, int *size){
    process temp=q[0];
    (*size)--;
    for (int j = 0; j< (*size) ; j++) {
        q[j] = q[j + 1];
    }
        return temp;

}

//Arrival time of all process is 0
int Arrivaltime =0;

//round robin function for process scheduling
void rr(process*q, int *size, int quntem, int swtch_time){
    printf("entered rr\n");

    while(swtch_time>0 && (*size)>0) {
        if (swtch_time >= quntem) {
            process exe = dequeue(q,size);
            if(exe.remaning_time>=quntem){
                swtch_time=swtch_time-quntem;
                totalTime=totalTime+quntem;
                exe.remaning_time=exe.remaning_time-quntem;
                if(exe.remaning_time==0){
                    exe.turnaround_time=totalTime-Arrivaltime;
                    exe.waiting_time=exe.turnaround_time-exe.brust_time;
                    printf("\n Process: %d is Finished",exe.p_id);
                    printf("\n\t>>Turnaround Time : %d",exe.turnaround_time);
                    printf("\n\t>>Waiting Time : %d",exe.waiting_time);

                }
                else{
                    printf("\n process not finished ");
                    enqueue(q,size,exe);
                }

            } else{
                swtch_time=swtch_time-exe.remaning_time;
                totalTime=totalTime+exe.remaning_time;
//                printf("\n process end ");
                exe.remaning_time=0;
                exe.turnaround_time=totalTime-Arrivaltime;
                exe.waiting_time=exe.turnaround_time-exe.brust_time;
                printf("\n Process: %d is Finished",exe.p_id);
                printf("\n\t>>Turnaround Time : %d",exe.turnaround_time);
                printf("\n\t>>Waiting Time : %d",exe.waiting_time);
            }
        }else{
            if(q[0].remaning_time<=swtch_time){
                swtch_time=swtch_time-q[0].remaning_time;
                q[0].remaning_time=0;
                q[0].turnaround_time=totalTime-Arrivaltime;
                q[0].waiting_time=q[0].turnaround_time-q[0].brust_time;
                dequeue(q,size);
                printf("\n process end ");
                printf("\n Process: %d is Finished",q[0].p_id);
                printf("\n\t>>Turnaround Time : %d",q[0].turnaround_time);
                printf("\n\t>>Waiting Time : %d",q[0].waiting_time);

            } else{
                q[0].remaning_time=q[0].remaning_time-swtch_time;
                swtch_time=0;
                printf("\n process not finished ");
            }
        }

    }
    printf("\n\n.... CPU EXECUTED TO NEXT QUEUE  ...\n");
}

void sjf(process *q,int *size,int swtch_time ){
    printf("entered sjp\n");
    while (swtch_time!=0 && *size>0){
        int s_j_f=0;
        for (int i = 0; i < (*size); ++i) {
            if(q[i].remaning_time<q[s_j_f].remaning_time){
                s_j_f=i;
            }
        }
        process exe= dequeue((q+s_j_f),size);

        if(exe.remaning_time>=swtch_time){

            exe.remaning_time=exe.remaning_time-swtch_time;
            totalTime+=swtch_time;
            swtch_time=0;
            if(exe.remaning_time==0){
                exe.turnaround_time=totalTime-Arrivaltime;
                exe.waiting_time=exe.turnaround_time-exe.brust_time;
                printf("\n process end ");
                printf("\n Process: %d is Finished",exe.p_id);
                printf("\n\t>>Turnaround Time : %d",exe.turnaround_time);
                printf("\n\t>>Waiting Time : %d",exe.waiting_time);

            } else{
                printf("\n process not finisied ");
                enqueue(q,size,exe);
            }
        }else{
            swtch_time=swtch_time-exe.remaning_time;
            totalTime=totalTime+exe.remaning_time;
            exe.remaning_time=0;

            exe.turnaround_time=totalTime-Arrivaltime;
            exe.waiting_time=exe.turnaround_time-exe.brust_time;
            printf("\n process end ");
            printf("\n Process: %d is Finished",exe.p_id);
            printf("\n\t>>Turnaround Time : %d",exe.turnaround_time);
            printf("\n\t>>Waiting Time : %d",exe.waiting_time);
        }

    }
    printf("\n\n.... CPU EXECUTED TO NEXT QUEUE  ...\n");
}

void fcfs(process*q,int *size,int swtch_time){
    printf("entered fcfs\n");
    while (swtch_time!=0 &&  *size >0 ){

        if(q[0].remaning_time>swtch_time){

            q[0].remaning_time=q[0].remaning_time-swtch_time;
            totalTime+=swtch_time;
            swtch_time=0;
        }else{
            swtch_time=swtch_time-q[0].remaning_time;
            totalTime+=q[0].remaning_time;
            q[0].remaning_time=0;

            q[0].turnaround_time=totalTime-Arrivaltime;
            q[0].waiting_time=q[0].turnaround_time-q[0].brust_time;
            dequeue(q,size);
            printf("\n Process: %d is Finished",q[0].p_id);
            printf("\n\t>>Turnaround Time : %d",q[0].turnaround_time);
            printf("\n\t>>Waiting Time : %d",q[0].waiting_time);
        }
    }
    printf("\n\n.... CPU EXECUTED TO NEXT QUEUE  ...\n");
}


int main() {
    int quntom=20;
    int swtch=20;
    int n;
    printf("enter No of Processes :");

    scanf("%d",&n);

printf("\n....... Multilevel Queue Scheduling Algorithem Implimentation .......\n\n");
    printf("Priority Queues: \n\n\t 0 > RR \n\t 1 > SJF \n\t 2 > SJF \n\t 3 > FCFS \n");

    for(int i=1;i<=n;i++){

        process new_process;
        new_process.p_id=i;

        printf("enter %d process burst time :",i);
        scanf("%d",&new_process.brust_time);


        printf("enter pryority :");
        scanf("%d",&new_process.priority);


        new_process.remaning_time=new_process.brust_time;

        switch (new_process.priority) {
            case 0:
                enqueue(q0,&size_q0,new_process);
                break;
            case 1:
                enqueue(q1,&size_q1,new_process);
                break;
            case 2:
                enqueue(q2,&size_q2,new_process);
                break;
            case 3:
                enqueue(q3,&size_q3,new_process);
                break;
        }
    }

    while ( size_q0 >0|| size_q1 >0|| size_q3 >0|| size_q2 >0){
        if(size_q0>0){
            rr(q0,&size_q0,quntom,swtch);
            printf("\n");
        }
        if(size_q1>0){
            sjf(q1,&size_q1,swtch);
            printf("\n");
        }
        if(size_q2>0){
            sjf(q2,&size_q2,swtch);
            printf("\n");
        }
        if(size_q3>0){
            fcfs(q3,&size_q3,swtch);
            printf("\n");
        }

    }
    printf("\n...... ALL QUEUES ARE EXECUTED......\n");
    printf("Total process Time : %d \n",totalTime);

    printf("\nAvarage process time : %d\n",totalTime/4);
    return 0;
}
