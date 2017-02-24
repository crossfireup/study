# web security
  * [owasp]()
  * WhiteHat Website Security Statistics Report
* hacking exposed web application
   * UGC(user-generated content) 

   * why
    1. ubiquity:
      everywhere and each time
    2. simple:
      text-based
    3. anonymity:
      throught vpn or tor
    4. bypass firewall:
      inbound http(s) is permitted by most typical firewall policies, and increases as more app move to http.
    5. custom code:
      easily configuring web develop platforms and most web apps assembled by unexperienced developer
    6. immature security:
      stateless, not implement session, basic authentication and authorization plumbing for http was bolted on years
      after it became popular
    7. constant change:
      developer, sysadmin, content manager touch a web application
    8. money:
      e-commerce, 
  
  * content
    1. web platform: web platforms vulnerabilities, including http server(IIS, apache, nginx);

    2. web application: authentication, authorization, site structure, input validation, application logic, and management interfaces;

    3. database: running privileged cmd via database query and query manipulation to return excessive datasets;

    4. web client: active content execution, client software vulnerability exploitation, cross-site scripting erros, and fraud-like phishing

    5. transport: eavasdropping on client-server communications and ssl redirection

    6. avalaibility: sensational "hacking" attacks DDos, 

    xperts will cite various “best-practices,” such as software security training for developers, security testing during QA, static code analysis, 
    centralized controls, Web Application Firewalls, penetration-testing, and more

  * tools
    1. IE
      * tempIE
      * IEWatch
      * IEHeader
    2. firefox
      * LiveHTTPHeader
      * TemperData
      * ModifyHeaders
    3. proxy
      * Paros Proxy

       SLMGR /REARM.

  - profiling
    - infrastracture profiling  
      - footprinting and scanning
        - Internet register research
        - DNS
        - general organization research
        - server discovery
        - nerwork service(port scanning)

      - banner grabbing
        ```
        nc 192.168.2.131 80
          HEAD / HTTP/1.0
          HOST: 192.168.2.131

          HTTP/1.1 200 OK
          Server: nginx/1.11.6
          Date: Thu, 23 Feb 2017 18:01:56 GMT
          Content-Type: text/html; charset=UTF-8
          Connection: close
          X-Powered-By: PHP/7.0.13

          nc 192.168.2.131 80
            PUT / HTTP/1.0

            HTTP/1.1 405 Not Allowed
            Server: nginx/1.11.6
            Date: Fri, 24 Feb 2017 15:52:08 GMT
            Content-Type: text/html
            Content-Length: 173
            Connection: close


        nc 192.168.1.3 8080
          PUT / HTTP/1.0

          HTTP/1.1 405 Method Not Allowed
          Server: Apache-Coyote/1.1
          Content-Type: text/html;charset=utf-8
          Content-Language: en
          Content-Length: 1086
          Date: Fri, 24 Feb 2017 07:49:49 GMT
          Connection: close

        nc 192.168.1.3 8080
          HEAD / HTTP/1.0

          HTTP/1.1 200 OK
          Server: Apache-Coyote/1.1
          Content-Type: text/html;charset=UTF-8
          Date: Fri, 24 Feb 2017 07:53:56 GMT
          Connection: close



      - advanced http fingerprinting
        - Unexpected http method
        - 

    - application profiling


* [xxs](https://translate.google.com/translate?sl=auto&tl=en&js=y&prev=_t&hl=en&ie=UTF-8&u=http%3A%2F%2Fmusana.net%2Fxss-detayli-dokuman.html&edit-text=)
  - reflected XXS

  - DOM-based XXS
    persistent and reflected xss vulnerabilities can be prevented by server-side filtering, 
    this is not the case with DOM-based xss;
    some of the queries served only in user's broswer without being transmited to server side;
    writen afeter '#'

  - stored(persistent) XXS
    occurs when the data from the user is not sufficiently filtered before it is recorded in the database, 
    and then the data that is recorded is to be extracted from the database for use elsewhere.