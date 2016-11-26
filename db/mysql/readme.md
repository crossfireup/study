# install mysql #
    * git clone https://github.com/mysql/mysql-server.git

    groupadd mysql
    useradd -r -g mysql mysql -s /sbin/nologin

    mkdir /opt/mysql /opt/mysql-files
    chown -R mysql:mysql /opt/mysql /opt/mysql-files
    chmod 750 /opt/mysql-files

    vim /etc/my.cnf
    datadir=/opt/mysql
	socket=/opt/mysql/mysql.sock

    mysqld --initialize --user=mysql

    /opt/mysql
    	mysql_ssl_rsa_setup
    

    [mysqld]

socket=/var/lib/mysql/mysql.sock 

[client]

socket=/var/lib/mysql/mysql.sock


mysqld_safe &

root :
service mysqld stop
mysqld_safe --skip-grant-tables &
mysql --user=root mysql
update user set Password=PASSWORD('new-password') where user='root';
update user set authentication_string=Password('new-password') where user='root';

flush privileges;
exit;


ps -e | grep  [m]ysqld_safe | awk '{print $1}' | sed -n 1p > /opt/mysql/mysqld_safe.pid

* host xxxx is not allowed to connect mysql server 
	CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';

	GRANT ALL PRIVILEGES ON *.* TO 'username'@'localhost' WITH GRANT OPTION;

	CREATE USER 'username'@'%' IDENTIFIED BY 'password';

	GRANT ALL PRIVILEGES ON *.* TO 'username'@'%' WITH GRANT OPTION;

	FLUSH PRIVILEGES;


	create user 'php'@'localhost' identified by 'Php2008.';
	grant all privileges on *.* to 'php'@'localhost' with grant option;
	create user 'php'@'%' identified by 'Php2008.';
	grant all privileges on *.* to 'php'@'%' with grant option;
	flush privileges;

* ERROR 1820 (HY000): You must reset your password using ALTER USER statement before executing this statement.
	UPDATE mysql.user SET Password=PASSWORD('your_new_password') 
       WHERE User='root'; 
	mysql> set password=password('Helloc2008.');
	ERROR 1819 (HY000): Your password does not satisfy the current policy requirements
