import asyncio
import websockets

async def client_websocket():
    uri = "ws://localhost:8000"
    
    async with websockets.connect(uri) as websocket:
        # Envoyer un message au serveur
        message = "Salut, serveur!"
        print(f"Envoyé: {message}")
        await websocket.send(message)

        # Attendre la réponse du serveur
        réponse = await websocket.recv()
        print(f"Reçu: {réponse}")

# Exécuter le client
asyncio.get_event_loop().run_until_complete(client_websocket())
