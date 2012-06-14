//
// "$Id$"
//
// FLTK3 connect library header file for the Fast Light Tool Kit (FLTK).
//
// Copyright 2002-2012 by Matthias Melcher and others.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
//
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
// USA.
//
// Please report all bugs and problems on the following page:
//
//     http://www.fltk.org/str.php
//

#ifndef Fltk3_TCP_Socket_H
#define Fltk3_TCP_Socket_H

/* \file
 fltk3::TCPSocket widget . */

#include <fltk3/Widget.h>
#include <fltk3/Group.h>

#ifdef WIN32
# include <winsock2.h>
#endif


namespace fltk3 {
  
  /**
   \brief A simple TCP connection.
   
   This class wraps fltk3::add_fd, fltk3::remove_fd, and friends in a simple
   package. 
   
   Connections can be managed via callbacks or by overriding the on_...
   methods in this class.
   
   \todo There are still a lot of useful features missing in this class.
   */
  class TCPSocket : public Widget
  {
    
  private:
    
    int pStatus;
    int pActive;
#ifdef WIN32
    SOCKET sListen;
    SOCKET sData;
    static char wsaStartup;
#else
    int fdListen;
    int fdData;
#endif
    int pPort;
    static void pListenCB(int, void*);
    static void pDataReadCB(int, void*);
    static void pDataExceptCB(int, void*);
    
  protected:
    
    void draw();
    
  public:
    
    enum Status {
      CLOSED, LISTENING, VERIFYING, CONNECTED
    };
    
    enum Event {
      CONNECT=128, RECEIVE, CLOSE
    };
    
    /**
     Create a widget that manages a TCP/IP network connection.
     This widget manages a network connection, displaying a graphic 
     representation of the connection state. If no visual feedback is 
     required, this widget can be hidden or not be put into the widget 
     hierarchy at all.
     */
    TCPSocket(int x, int y, int w, int h, const char *l);
    
    /**
     Disconnect and return resources
     */
    virtual ~TCPSocket();
    
    // server methods
    
    /**
     Listen on a port for incomming network connections.
     */
    char listen(unsigned short port);
    
    /**
     Reject an incomming connection.
     This method is usually called from within on_connect().
     */
    char reject();
    
    /**
     Accept an incomming connection.
     This method is usually called from within on_connect().
     */
    char accept();
    
    // client methods
    
    /**
     Attempt a connection to another TCP/IP socket in liestening mode.
     */
    int connect(unsigned char ip0, unsigned char ip1, unsigned char ip2, unsigned char ip3, unsigned short port);
    
    // shared methods
    
    /**
     Send a datablock over the network connection.
     */
    char send(const void *data, int size);
    
    /**
     Send some text, terminated by NUL.
     */
    char send(const char *text);
    
    /**
     Receive data until the buffer is filled.
     \todo Code on Unix is missing the loop.
     */
    int recv_all(void *data, int size);
    
    /**
     Receive data until the buffer is filled or a datablock ends.
     */
    int recv(void *data, int size);
    
    /**
     Receive the next block of data, but don;t remove it from the queue.
     */
    int peek(void *data, int size);
    
    /**
     Close a server or client connection.
     */
    void close();
    
    /**
     Override this method to get notified whenever a client attempts to connect.
     */
    virtual char on_connect();
    
    /**
     Override this method to get notified whenever data arrives.
     */
    virtual char on_receive();
    
    /**
     Override this method to get notified whenever the connection is terminated.
     */
    virtual char on_close();
    
    /**
     Return the current state of the connection.
     */
    int status() const;
    
    /**
     Return the number of bytes available in the buffer.
     */
    int available() const;
    
    /**
     Flush a number of bytes from the receive buffer.
     */
    void flush_input(int n=-1);
    
  };
  
  
} // namespace

#endif

//
// End of "$Id$".
//