/**
 * @file server.cpp
 * @brief Servidor IRC ultra mega básico usando sockets y poll en C++
 *
 * Este programa implementa un servidor recontra básico que escucha en el puerto
 * definido (por defecto 8080) y gestiona conexiones entrantes utilizando la
 * función poll() para monitorizar múltiples sockets.
 *
 * Funcionalidades:
 * - Creación y configuración de un socket para el servidor.
 * - Aceptación de nuevas conexiones con accept().
 * - Lectura y escritura en sockets de clientes usando recv() y send().
 * - Gestión de desconexiones de clientes.
 */

#include <arpa/inet.h>
#include <arpa/inet.h> // Para funciones de red (inet_pton, htons, etc.)
#include <cstdio>
#include <cstdlib> // Para EXIT_FAILURE / EXIT_SUCCESS
#include <cstring> // Para memset()
#include <iostream>
#include <netinet/in.h>
#include <poll.h>       // Para poll()
#include <sys/socket.h> // Para funciones de sockets
#include <unistd.h>     // Para close()
#include <vector>

#define PORT 8080 // Puerto en el que el servidor escuchará

/**
 * @brief Función principal del servidor IRC.
 *
 * Se encarga de crear y configurar el socket, ponerlo en modo escucha, y luego
 * gestionar las conexiones entrantes y la comunicación con los clientes
 * mediante poll().
 *
 * @return int EXIT_SUCCESS si todo sale bien, EXIT_FAILURE en caso de error.
 */
int main() {
  int server_fd, client_socket;
  int opt = 1;
  struct sockaddr_in address;
  socklen_t addrlen = sizeof(address);

  /* Creación y configuración del socket del servidor */
  /**
   * @brief Crea un socket de tipo IPv4/TCP.
   *
   * @param AF_INET: Especifica el uso de IPv4.
   * @param SOCK_STREAM: Indica el uso de una conexión orientada a flujo (TCP).
   * @param 0: Protocolo por defecto (TCP).
   *
   * @return Un descriptor de socket (int) o -1 en caso de error.
   */
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Error al crear el socket");
    return EXIT_FAILURE;
  }

  /**
   * @brief Configura el socket para permitir la reutilización de la dirección
   * (SO_REUSEADDR).
   *
   * @param server_fd: Descriptor del socket.
   * @param SOL_SOCKET: Nivel de la opción (socket general).
   * @param SO_REUSEADDR: Opción para permitir reutilizar la dirección.
   * @param &opt: Valor de la opción (1 para habilitar).
   * @param sizeof(opt): Tamaño del valor de la opción.
   *
   * @return 0 en caso de éxito, -1 en caso de error.
   */
  if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
    perror("Error en setsockopt");
    return EXIT_FAILURE;
  }

  /* Configuración de la dirección y vinculación con bind() */
  /**
   * @brief Configura la estructura sockaddr_in con la dirección y puerto del
   * servidor.
   *
   * - sin_family: Debe ser AF_INET para IPv4.
   * - sin_addr.s_addr: Se establece en INADDR_ANY para escuchar en todas las
   * interfaces.
   * - sin_port: Puerto en orden de red (se usa htons() para la conversión).
   */
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY; // Escucha en todas las interfaces
  address.sin_port = htons(PORT);       // Convierte el puerto al formato de red

  /**
   * @brief Asocia el socket a la dirección IP y puerto especificados.
   *
   * @param server_fd: Descriptor del socket.
   * @param (struct sockaddr *)&address: Puntero a la estructura con la
   * dirección.
   * @param sizeof(address): Tamaño de la estructura.
   *
   * @return 0 en caso de éxito, -1 en caso de error.
   */
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Error en bind");
    return EXIT_FAILURE;
  }

  /* Poner el socket en modo escucha con listen() */
  /**
   * @brief Marca el socket como escuchando conexiones entrantes.
   *
   * @param server_fd: Descriptor del socket.
   * @param 3: Backlog, número máximo de conexiones pendientes en la cola.
   *
   * @return 0 en caso de éxito, -1 en caso de error.
   */
  if (listen(server_fd, 5) < 0) {
    perror("Error en listen");
    return EXIT_FAILURE;
  }
  std::cout << "Servidor escuchando en el puerto " << PORT << "...\n";

  /* Inicialización de poll() */
  /**
   * @brief Crea un vector para almacenar las estructuras pollfd que se usarán
   * para monitorear los descriptores de archivo (sockets).
   *
   * Cada estructura pollfd contiene:
   *   - fd: Descriptor del socket.
   *   - events: Eventos que se desean monitorear (ej. POLLIN para datos
   * disponibles).
   *   - revents: Eventos que ocurrieron (rellenado por poll() al detectar
   * actividad).
   */
  std::vector<pollfd> poll_fds;

  // Se configura la estructura pollfd para el socket del servidor.
  pollfd server_poll;
  server_poll.fd = server_fd; // Descriptor del socket del servidor
  server_poll.events =
      POLLIN; // Se monitorea la llegada de datos (nuevas conexiones)
  poll_fds.push_back(server_poll); // Se añade al vector de pollfd

  /* Bucle principal para gestionar conexiones y comunicación */
  while (true) {
    /**
     * @brief Espera a que alguno de los descriptores monitoreados tenga
     * actividad.
     *
     * @param poll_fds.data(): Puntero al primer elemento del vector.
     * @param poll_fds.size(): Número de descriptores a monitorizar.
     * @param -1: Tiempo de espera infinito (poll() bloquea hasta que ocurra un
     * evento).
     *
     * @return Número de descriptores con eventos o -1 en caso de error.
     */
    int poll_count = poll(poll_fds.data(), poll_fds.size(), -1);
    if (poll_count < 0) {
      perror("Error en poll");
      break;
    }

    // Itera sobre cada descriptor en el vector para manejar los eventos.
    for (size_t i = 0; i < poll_fds.size(); ++i) {
      // Comprueba si se produjo un evento de entrada (POLLIN) en este
      // descriptor.
      if (poll_fds[i].revents & POLLIN) {
        // Si el evento se produce en el socket del servidor, es una nueva
        // conexión.
        if (poll_fds[i].fd == server_fd) {
          /**
           * @brief Acepta una nueva conexión entrante.
           *
           * @param server_fd: Descriptor del socket del servidor.
           * @param (struct sockaddr *)&address: Puntero a la estructura que
           * recibirá la dirección del cliente.
           * @param &addrlen: Tamaño de la estructura de dirección.
           *
           * @return Un nuevo descriptor de socket para el cliente o -1 en caso
           * de error.
           */
          client_socket =
              accept(server_fd, (struct sockaddr *)&address, &addrlen);
          if (client_socket < 0) {
            perror("Error en accept");
            continue;
          }
          std::cout << "Nueva conexión aceptada: fd " << client_socket << "\n";

          // Configura la estructura pollfd para el nuevo cliente.
          pollfd client_poll;
          client_poll.fd = client_socket;  // Descriptor del socket del cliente.
          client_poll.events = POLLIN;     // Se monitorea la llegada de datos.
          poll_fds.push_back(client_poll); // Se añade el descriptor al vector.
        } else {
          /**
           * @brief Lee los datos enviados por un cliente.
           *
           * @param poll_fds[i].fd: Descriptor del socket del cliente.
           * @param buffer: Array donde se almacenarán los datos.
           * @param sizeof(buffer) - 1: Tamaño máximo a leer (se reserva espacio
           * para el terminador nulo).
           * @param 0: Flags (sin flags especiales).
           *
           * @return Número de bytes leídos, 0 si el cliente se desconectó o -1
           * en caso de error.
           */
          char buffer[1024];
          int bytes_read = recv(poll_fds[i].fd, buffer, sizeof(buffer) - 1, 0);
          if (bytes_read <= 0) {
            // Si no se reciben datos, el cliente se ha desconectado o se
            // produjo un error.
            if (bytes_read == 0)
              std::cout << "Cliente desconectado: fd " << poll_fds[i].fd
                        << "\n";
            else
              perror("Error en recv");

            /**
             * @brief Cierra el socket del cliente y elimina su descriptor del
             * vector.
             *
             * @param poll_fds[i].fd: Descriptor del socket a cerrar.
             */
            close(poll_fds[i].fd);
            poll_fds.erase(poll_fds.begin() + i);
            --i; // Ajusta el índice tras eliminar el elemento.
          } else {
            buffer[bytes_read] = '\0';
            std::cout << "Mensaje recibido de fd " << poll_fds[i].fd << ": "
                      << buffer << "\n";

            /**
             * @brief Envía de vuelta (eco) los datos recibidos al cliente.
             *
             * @param poll_fds[i].fd: Descriptor del socket del cliente.
             * @param buffer: Datos a enviar.
             * @param bytes_read: Número de bytes a enviar.
             * @param 0: Flags (sin flags especiales).
             *
             * @return Número de bytes enviados o -1 en caso de error.
             */
            if (send(poll_fds[i].fd, buffer, bytes_read, 0) < 0)
              perror("Error en send");
          }
        }
      }
    }
  }

  // Cierra el socket del servidor antes de finalizar.
  close(server_fd);
  return EXIT_SUCCESS;
}
