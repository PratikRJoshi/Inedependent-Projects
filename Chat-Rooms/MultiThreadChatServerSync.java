import java.net.*;
import java.io.*;

public class MultiThreadChatServerSync {
	 // The server socket.
	  private static ServerSocket serverSocket = null;
	  // The client socket.
	  private static Socket clientSocket = null;

	  // This chat server can accept up to maxClientsCount clients' connections.
	  private static final int maxClientsCount = 10;
	  private static final clientThreadSync[] threads = new clientThreadSync[maxClientsCount];
	  
	  public static void main(String args[]){
		  //The default port number
		  int portNumber = 2222;
		  if (args.length < 1) {
		      System.out.println("Usage: java MultiThreadChatServerSync <portNumber>\n" + "Now using port number=" + portNumber);
		  } 
		  else {
		      portNumber = Integer.valueOf(args[0]).intValue();
		  }
		  /*We cannot choose a port less than 1023 if we are not privileged users.*/
		  try {
		      serverSocket = new ServerSocket(portNumber);
		      System.out.println("Server is running at IP of: "+InetAddress.getLocalHost().getHostAddress());
		  } 
		  catch (IOException e) {
			  System.out.println(e);
		  }
		  /*Create a client socket for each connection and pass it to a new client thread.*/
		  while (true) {
			  try {
				  clientSocket = serverSocket.accept();
				  int i = 0;
				  for (i = 0; i < maxClientsCount; i++) {
					  if (threads[i] == null) {
						  (threads[i] = new clientThreadSync(clientSocket, threads)).start();
						  break;
					  }
				  }
				  if (i == maxClientsCount) {
					  PrintStream os = new PrintStream(clientSocket.getOutputStream());
					  os.println("Server too busy. Try later.");
					  os.close();
					  clientSocket.close();
				  }
		      } 
			  catch (IOException e) {
				  e.printStackTrace();
		      }
		  }
	  }
}

/*
 * The chat client thread. This client thread opens the input and the output
 * streams for a particular client, ask the client's name, informs all the
 * clients connected to the server about the fact that a new client has joined
 * the chat room, and as long as it receive data, echos that data back to all
 * other clients. The thread broadcast the incoming messages to all clients and
 * routes the private message to the particular client. When a client leaves the
 * chat room this thread informs also all the clients about that and terminates.
 */
class clientThreadSync extends Thread {

	private String clientName = null;
	private BufferedReader is = null;
	private PrintStream os = null;
	private Socket clientSocket = null;
	private final clientThreadSync[] threads;
  	private int maxClientsCount;

  	public clientThreadSync(Socket clientSocket, clientThreadSync[] threads) {
  		this.clientSocket = clientSocket;
  		this.threads = threads;
  		maxClientsCount = threads.length;
  	}
  	
  	public void run(){
  		int maxClientsCount = this.maxClientsCount;
  		clientThreadSync[] threads = this.threads;
  		
  		try{
  			is = new BufferedReader(new InputStreamReader(clientSocket.getInputStream()));
  			os = new PrintStream(clientSocket.getOutputStream());
  			String name;
  			
  			while(true){
  				os.println("Enter your name");
  				name = is.readLine();
  				if(name.indexOf('@')==-1)
  					break;
  				else
  					os.println("The name should not contain '@' in it.");
  			}
  			os.println("Welcome " + name+ " to our chat room.\nTo leave enter quit in a new line.");
  			synchronized (this) {
				for(int i=0;i<maxClientsCount;i++){
					if (threads[i] != null && threads[i] == this){
			            clientName = "@" + name;
			            break;
			        }
				}
				for (int i = 0; i < maxClientsCount; i++) {
					if (threads[i] != null && threads[i] != this) {
						threads[i].os.println("*** A new user " + name+ " entered the chat room !!! ***");
			        }
			    }
			}
  			/*Conversation begins here*/
  			while(true){
  				String line = is.readLine();
  				if(line.startsWith("quit"))
  					break;
  				/*Send private messages to the specific client*/
  				if(line.startsWith("@")){
  					String words[] = line.split("\\s", 2);
  					if(words.length>1 && words[1]!=null){
  						words[1] = words[1].trim();
  						if(!words[1].isEmpty()){
  							synchronized (this) {
  								for (int i = 0; i < maxClientsCount; i++) {
  				                  if (threads[i] != null && threads[i] != this && threads[i].clientName != null && threads[i].clientName.equals(words[0])) {
  				                	  threads[i].os.println("<" + name + "> " + words[1]);
  				                	  /*Echo this message to let the client know the private message was sent.*/
  				                	  this.os.println(">" + name + "> " + words[1]);
  				                	  break;
  				                  }
  				               }
							}
  						}
  					}
  				}
  				else{
  					/*The message is public, broadcast it to all other clients*/
  					synchronized (this) {
  						for (int i = 0; i < maxClientsCount; i++) {
  							if (threads[i] != null && threads[i].clientName != null) {
  								threads[i].os.println("<" + name + "> " + line);
  							}
  			            }
					}
  				}
			}
  			synchronized (this) {
  				for (int i = 0; i < maxClientsCount; i++) {
  					if (threads[i] != null && threads[i] != this && threads[i].clientName != null) {
  						threads[i].os.println("*** The user " + name+ " is leaving the chat room !!! ***");
  					}
  		        }
			}
  			os.println("*** Bye " + name + " ***");
  			synchronized (this) {
  				for (int i = 0; i < maxClientsCount; i++) {
  					if (threads[i] == this) {
  						threads[i] = null;
  					}
  		        }
  			}
  			is.close();
  			os.close();
  			clientSocket.close();
  		}
  		catch(Exception e){
  			
  		}
  	}
}