#include <arpa/inet.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <poll.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <unistd.h>

#define PORT 8080        // Puerto en el que ircserv escucha
#define NUM_CLIENTS 1000 // Numero de clientes que se conectaran

void run_client(int client_id) {
  // Crear un socket para el cliente (IPv4/TCP)
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0) {
    std::cerr << "Cliente " << client_id << ": Error al crear socket.\n";
    return;
  }

  // Configurar la dirección del servidor (localhost y puerto PORT)
  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;   // IPv4
  server_addr.sin_port = htons(PORT); // Puerto en orden de red
  if (inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr) <= 0) {
    std::cerr << "Cliente " << client_id << ": Error en inet_pton.\n";
    close(sock);
    return;
  }

  // Conectar al servidor ft_irc
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    std::cerr << "Cliente " << client_id << ": Error en connect.\n";
    close(sock);
    return;
  }

  // Crear un mensaje personalizado para este cliente
  char msg[128];
  sprintf(msg, "Hello from client %d", client_id);

  // Enviar el mensaje al servidor
  ssize_t sent_bytes = send(sock, msg, strlen(msg), 0);
  if (sent_bytes < 0) {
    std::cerr << "Cliente " << client_id << ": Error en send.\n";
    close(sock);
    return;
  }

  // Buffer para recibir el eco del servidor
  char buffer[1024];
  ssize_t received_bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
  if (received_bytes < 0) {
    std::cerr << "Cliente " << client_id << ": Error en recv.\n";
    close(sock);
    return;
  }
  buffer[received_bytes] = '\0'; // Terminar la cadena recibida

  // Verificar que el mensaje recibido es igual al enviado
  if (strcmp(msg, buffer) != 0) {
    std::cerr << "Cliente " << client_id << ": Test fallido, se esperaba \""
              << msg << "\" y se recibió \"" << buffer << "\"\n";
  } else {
    std::cout << "Cliente " << client_id << ": Test exitoso.\n";
  }

  // Cerrar el socket del cliente
  close(sock);
}

int main() {
  // Crear un proceso hijo para ejecutar el servidor ircserv
  pid_t pid = fork();
  if (pid < 0) {
    perror("Error en fork");
    return EXIT_FAILURE;
  }

  if (pid == 0) {
    execl("./ircserv", "./ircserv", (char *)NULL);
    perror("Error en execl");
    exit(EXIT_FAILURE);
  }

  sleep(1);

  // Crear múltiples procesos para simular clientes
  int i = 0;
  for (i = 0; i < NUM_CLIENTS; i++) {
    pid_t client_pid = fork();
    if (client_pid == 0) {
      run_client(i);
      exit(EXIT_SUCCESS);
    }
  }

  for (int j = 0; j < NUM_CLIENTS; j++) {
    wait(NULL);
  }

  // Finalizar el proceso del servidor
  kill(pid, SIGTERM);
  wait(NULL);

  std::cout << i << " clientes han completado sus pruebas." << std::endl;

  return EXIT_SUCCESS;
}
