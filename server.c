#include <stdio.h> //io, pretty obvious
#include <stdlib.h> //stdlib, ...
#include <string.h> //string-uri :(
#include <sys/socket.h> //Socketuri retele etc...
#include <errno.h> //Erori
#include <unistd.h> //Sleepy
#include <netinet/in.h> //Adresa pentru socket
#include <pthread.h> //Multithreading

//Aici facem un server pentru aplicatia noastra de mesaje.
//Initial o voi testa cu nc in plain text
//To do:
//encryption
//file sending
//sa fie safe din punct de vedere a securitatii, adica fara buffer overflow:(

void dots(int nr_dots){ //animatie frumoasa pentru incarcare si asteptare
    fflush(stdout);
    sleep(1);
    for(int i=0; i < nr_dots; i++){
        printf("%c", '.');
        fflush(stdout);
        sleep(1);
    }
}

//int clientthread()

int main(int argc, char* argv[]){

    for(int i=1; i < argc; i++){ //Daca avem argumentul pentru help afisam instructiunile si iesim din program
        if(!(strcmp(argv[i], "-h")) || !(strcmp(argv[i], "--help"))){
            printf("%s\n%s%s", "Usage:", argv[0], " [OPTION]");
            return 0;
        }
    }

    printf("hello 🐢\nCreating socket"); //Proba de microfon:)
    dots(3);
    int fd = socket(AF_INET, SOCK_STREAM, 0); //Facem socketu
    if(fd == -1){ //In caz de eroare iesim din program
        printf("\n%s", "Error: socket kaput, ");
        if(errno == EACCES){
            printf("%s", "no permission:(");
        }
        else{
            printf("%s", "we don't know why:(");
        }
        return -1;
    }

    printf("Binding socket");
    dots(3);
    int port = 60065;
    for(int i=1; i < argc; i++){ //Verificam daca avem argument pentru port
        if(!(strcmp(argv[i], "-p"))){
            port = atoi(argv[i+1]);
        }
    }
    printf("Using port %d", port);
    dots(3);

    struct sockaddr_in servaddr; //Definim adresa la care ascultam si client-ul
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(fd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1){ //Legam socket-ul nostru la o adresa si un port
        printf("\n%s", "Error: binding kaput, ");
        if(errno == EACCES){
            printf("%s", "no permission:(");
        }
        else{
            printf("%s", "we don't know why:(");
        }
        return -1;
    }
    printf("\n%s", "All doneeeeee🤗"); //Am terminat initializarea

    struct sockaddr_in cl1addr, cl2addr;
    uint cl1addrlen = sizeof(cl1addr), cl2addrlen = sizeof(cl2addr);

    listen(fd, 0); //Ascultam pentru conexiuni
    printf("\n%s", "Incoming connection...");
    int cl1fd = accept(fd, (struct sockaddr *)&cl1addr, &cl1addrlen); //Acceptam conexiunea cu cl1
    if(cl1fd == -1){ //Daca nu a reusit conexiunea iesim din program
        printf("%s", "Connection failed:(");
        return -1;
    }
    else{
        printf("%s", "Client1 connected succesfully, receiving");
    }
    char welcome[] = "Heloooooooooo🐢🐢🐢";
    write(cl1fd, welcome, sizeof(welcome));
    char readbuf[64];
    read(cl1fd, readbuf, sizeof(readbuf));
    printf("\n%s%s", "Received: ", readbuf);
    close(cl1fd);
    close(fd);

    return 0;
}
