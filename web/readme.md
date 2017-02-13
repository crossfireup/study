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

