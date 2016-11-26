# install #
    * the PCRE library – required by NGINX Core and Rewrite modules and provides support for regular expressions:
        $ wget ftp://ftp.csx.cam.ac.uk/pub/software/programming/pcre/pcre-8.39.tar.gz
        $ tar -zxf pcre-8.39.tar.gz
        $ cd pcre-8.39
        $ ./configure
        $ make
        $ sudo make install
    * the zlib library – required by NGINX Gzip module for headers compression:
        $ wget http://zlib.net/zlib-1.2.8.tar.gz
        $ tar -zxf zlib-1.2.8.tar.gz
        $ cd zlib-1.2.8
        $ ./configure
        $ make
        $ sudo make install

    * the OpenSSL library – required by NGINX SSL modules to support the HTTPS protocol:

        $ wget http://www.openssl.org/source/openssl-1.0.2f.tar.gz
        $ tar -zxf openssl-1.0.2f.tar.gz
        $ cd openssl-1.0.2f
        $ ./configure darwin64-x86_64-cc --prefix=/usr
        $ make
        $ sudo make install

    * To download and unpack source files for the latest mainline version, type-in the commands:
        $ wget http://nginx.org/download/nginx-1.11.6.tar.gz
        $ tar zxf nginx-1.11.6.tar.gz
        $ cd nginx-1.11.6
        $ ./configure \
    --prefix=/etc/nginx \
    --sbin-path=/usr/sbin/nginx \
    --conf-path=/etc/nginx/nginx.conf \
    --error-log-path=/var/log/nginx/error.log \
    --http-log-path=/var/log/nginx/access.log \
    --pid-path=/var/run/nginx.pid \
    --lock-path=/var/run/nginx.lock \
    --http-client-body-temp-path=/var/cache/nginx/client_temp \
    --http-proxy-temp-path=/var/cache/nginx/proxy_temp \
    --http-fastcgi-temp-path=/var/cache/nginx/fastcgi_temp \
    --http-uwsgi-temp-path=/var/cache/nginx/uwsgi_temp \
    --http-scgi-temp-path=/var/cache/nginx/scgi_temp \
    --user=nginx \
    --group=nginx \
    --with-http_ssl_module \
    --with-http_realip_module \
    --with-http_addition_module \
    --with-http_sub_module \
    --with-http_dav_module \
    --with-http_flv_module \
    --with-http_mp4_module \
    --with-http_gunzip_module \
    --with-http_gzip_static_module \
    --with-http_random_index_module \
    --with-http_secure_link_module \
    --with-http_stub_status_module \
    --with-http_auth_request_module \
    --with-threads \
    --with-stream \
    --with-stream_ssl_module \
    --with-http_slice_module \
    --with-mail \
    --with-mail_ssl_module \
    --with-file-aio \
    --with-http_v2_module \
    --with-ipv6 \
    --with-pcre=../pcre-8.39
    

Packages for mainline version also have the following arguments:

    --with-stream_realip_module

nginx config:
    groupadd nginx 
    useradd  nginx -g nginx

    init shell:
    #!/bin/sh
    #
    # nginx - this script starts and stops the nginx daemin
    #
    # chkconfig:   - 85 15
    # description:  Nginx is an HTTP(S) server, HTTP(S) reverse \
    #               proxy and IMAP/POP3 proxy server
    # processname: nginx
    # config:      /etc/nginx/nginx.conf
    # pidfile:     /var/run/nginx.pid
    # user:        nginx

    # Source function library.
    . /etc/rc.d/init.d/functions

    # Source networking configuration.
    . /etc/sysconfig/network

    # Check that networking is up.
    [ "$NETWORKING" = "no" ] && exit 0

    nginx="/usr/sbin/nginx"
    prog=$(basename $nginx)

    NGINX_CONF_FILE="/etc/nginx/nginx.conf"

    lockfile=/var/run/nginx.lock

    start() {
        [ -x $nginx ] || exit 5
        [ -f $NGINX_CONF_FILE ] || exit 6
        echo -n $"Starting $prog: "
        daemon $nginx -c $NGINX_CONF_FILE
        retval=$?
        echo
        [ $retval -eq 0 ] && touch $lockfile
        return $retval
    }

    stop() {
        echo -n $"Stopping $prog: "
        killproc $prog -QUIT
        retval=$?
        echo
        [ $retval -eq 0 ] && rm -f $lockfile
        return $retval
    }

    restart() {
        configtest || return $?
        stop
        start
    }

    reload() {
        configtest || return $?
        echo -n $"Reloading $prog: "
        killproc $nginx -HUP
        RETVAL=$?
        echo
    }

    force_reload() {
        restart
    }

    configtest() {
    $nginx -t -c $NGINX_CONF_FILE
    }

    rh_status() {
        status $prog
    }

    rh_status_q() {
        rh_status >/dev/null 2>&1
    }

    case "$1" in
        start)
            rh_status_q && exit 0
            $1
            ;;
        stop)
            rh_status_q || exit 0
            $1
            ;;
        restart|configtest)
            $1
            ;;
        reload)
            rh_status_q || exit 7
            $1
            ;;
        force-reload)
            force_reload
            ;;
        status)
            rh_status
            ;;
        condrestart|try-restart)
            rh_status_q || exit 0
                ;;
        *)
            echo $"Usage: $0 {start|stop|status|restart|condrestart|try-restart|reload|force-reload|configtest}"
            exit 2
    esac

    chmod +x /etc/init.d/nginx

    chkconfig --add nginx
    chkconfig --level 345 nginx on

    service nginx start 

    iptables -t filter -I INPUT -p tcp --dport 80 -j ACCEPT
    iptables -t filter -L INPUT --line-numbers
    iptables-save

rpm -ql pcre


# gcc #
    The compiler option -D can be used to define the macro MY_MACRO from command line.