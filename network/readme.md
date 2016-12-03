# introduction
    http://www.kegel.com/c10k.html

# [session](https://en.wikipedia.org/wiki/Session_%28computer_science%29)
  session is a semi-permanent interactive information interchange, also known as a dialogue, 
  a conversation or a meeting, between two or more communicating devices, 
  or between a computer and user (see Login session).

  Communication Transport may be implemented as part of protocols and services at the application layer, at the session layer or at the transport layer in the OSI model.

  * Application layer examples:

     * HTTP sessions, which allow associating information with individual visitors
     * A telnet remote login session

  * Session layer example:

    A Session Initiation Protocol (SIP) based Internet phone call

  * Transport layer example:
    
    A TCP session, which is synonymous to a TCP virtual circuit, 
    a TCP connection, or an established TCP socket.

# cgi
  
  * ISAPI (like NSAPI for Netscape or ASAPI for Apache)
    
    The Internet Server Application Programming Interface (ISAPI) is an N-tier API of Internet Information Services (IIS), 
    Microsoft's collection of Windows-based web server services. The most prominent application of IIS and ISAPI is Microsoft's web server.

    he ISAPI has also been implemented by Apache's mod_isapi module so that server-side web applications written for Microsoft's IIS can be used with Apache, 
    and other third-party web servers like Zeus Web Server offer ISAPI interfaces.
  
  * fastcgi vs cgi

    Instead of creating a new process for each request, FastCGI uses persistent processes to handle a series of requests.
     These processes are owned by the FastCGI server, not the web server.

     the separation of web applications from the web server in FastCGI has many advantages over embedded interpreters (mod_perl, mod_php, etc.):
     
       __allows server and application processes to be restarted independently__

       __enables the implementation of per-application / hosting service security policies,
         which is an important requirement for ISPs and web hosting companies__