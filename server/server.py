import asyncio
import websockets
import threading

async def gestionnaire_websocket(websocket, chemin):
    # La fonction de gestionnaire qui sera appelée à chaque nouvelle connexion WebSocket
    print(f"Connexion établie avec {websocket}")

    try:
        # Attendez les messages du client
        async for message in websocket:
            print(f"Reçu: {message}")

            # Répondre au client
            réponse = f"Reçu votre message: {message}"
            await websocket.send(réponse)
            print(f"Envoyé: {réponse}")

    except websockets.exceptions.ConnectionClosed:
        print(f"La connexion avec {websocket} a été fermée")



def lancer_serveur():
    # Créer une nouvelle boucle d'événements dans le thread
    boucle = asyncio.new_event_loop()
    asyncio.set_event_loop(boucle)

    # Configurer le serveur WebSocket
    serveur = websockets.serve(gestionnaire_websocket, "localhost", 8000)

    print("Serveur WebSocket en attente sur ws://localhost:8000")

    # Lancer le serveur dans la boucle asyncio du thread
    boucle.run_until_complete(serveur)
    boucle.run_forever()



# Créer un thread pour le serveur WebSocket
serveur_thread = threading.Thread(target=lancer_serveur)

# Démarrer le thread du serveur
serveur_thread.start()

# Attendre que le thread du serveur se termine (peut être omis si votre programme principal continue)
serveur_thread.join()


# attention problème de concurrence possible