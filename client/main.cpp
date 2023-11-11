#include "client.hpp"

int main()
{
  boost::asio::io_context ioc;

  std::string host = "localhost";
  std::string port = "8000";

  // ajouter un try catch

  WebSocketClient ws_client(ioc, host, port);

  // Envoi d'un message au serveur
  ws_client.send("Salut, serveur!");

  // Réception des messages du serveur (asynchrone)
  ws_client.receive();

  // Attendre jusqu'à ce que l'utilisateur appuie sur une touche pour fermer le client
  std::cout << "Appuyez sur Entrée pour fermer le client..." << std::endl;
  std::cin.get();

  // Fermer la connexion WebSocket
  ws_client.close();

  return 0;
}
