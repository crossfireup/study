orcle install:
1. config system parameter:
    grep MemTotal /proc/meminfo
    grep SwapTotal /proc/meminfo
        mount -t tmpfs shmfs -o size=6g /dev/shm

    df -h /dev/shm/
    Filesystem      Size  Used Avail Use% Mounted on
    shmfs           6.0G     0  6.0G   0% /dev/shm


su - root


Add groups

--required groups
/usr/sbin/groupadd -g 501 oinstall
/usr/sbin/groupadd -g 502 dba
/usr/sbin/groupadd -g 503 oper


Add user Oracle
/usr/sbin/useradd -u 502 -g oinstall -G dba,oper oracle
Change password for user

kernel.sem = 250 32000 100 128
250     32000   32      128
These values represent SEMMSL, SEMMNS, SEMOPM, and SEMMNI.

passwd oracle
Add kernel parameters to /etc/sysctl.conf
kernel.shmmni = 4096 
kernel.shmmax = 4398046511104
kernel.shmall = 1073741824
kernel.sem = 250 32000 100 128

fs.aio-max-nr = 1048576
fs.file-max = 6815744
net.ipv4.ip_local_port_range = 9000 65500
net.core.rmem_default = 262144
net.core.rmem_max = 4194304
net.core.wmem_default = 262144
net.core.wmem_max = 1048586
Apply kernel parameters

/sbin/sysctl -p
Add following lines to set shell limits for user oracle in file /etc/security/limits.conf

oracle   soft   nproc    131072
oracle   hard   nproc    131072
oracle   soft   nofile   131072
oracle   hard   nofile   131072
oracle   soft   core     unlimited
oracle   hard   core     unlimited
oracle   soft   memlock  50000000
oracle   hard   memlock  50000000
The “/etc/hosts” file must contain a fully qualified name for the server.

<IP-address>  <fully-qualified-machine-name>  <machine-name>
For example.

127.0.0.1 centos7 centos7.dbaora.com localhost localhost.localdomain
Verify your network settings

[root@centos7 ~]# ping -c 1 centos7
PING centos7 (127.0.0.1) 56(84) bytes of data.
64 bytes from centos7 (127.0.0.1): icmp_seq=1 ttl=64 time=0.040 ms

-# centos7 ping statistics ---
1 packets transmitted, 1 received, 0% packet loss, time 0ms
rtt min/avg/max/mdev = 0.040/0.040/0.040/0.000 ms
Modify .bash_profile for user oracle in his home directory

# Oracle Settings


# /etc/profile.d/oraevn.sh
export TMP=/tmp

export DISPLAY=192.168.1.128:0.0

export ORACLE_HOSTNAME=hky.dev.centos.com
export ORACLE_SID=ora11g
export ORACLE_BASE=/oracle/ora11g
export ORACLE_HOME=$ORACLE_BASE/product

PATH=$PATH:$ORACLE_HOME/bin

export LD_LIBRARY_PATH=$ORALCE_HOME/lib:$LD_LIBRARY_PATH
export CLASSPATH=$ORALCE_HOME/JLIB:$ORACLE_HOME/RDBMS/jlib;

umask 022

Check which packages are installed and which are missing

rpm -q --qf '%{NAME}-%{VERSION}-%{RELEASE}(%{ARCH})\n' binutils \
elfutils-libelf \
elfutils-libelf-devel \
gcc \
gcc-c++ \
glibc \
glibc-common \
glibc-devel \
glibc-headers \
ksh \
libaio \
libaio-devel \
libgcc \
libstdc++ \
libstdc++-devel \
make \
sysstat \
unixODBC \
unixODBC-devel
In my case it returns following

binutils-2.20.51.0.2-5.11.el6 (x86_64)
compat-libcap1-1.10-1 (x86_64)
compat-libstdc++-33-3.2.3-69.el6 (x86_64)
compat-libstdc++-33-3.2.3-69.el6.i686
gcc-4.4.4-13.el6 (x86_64)
gcc-c++-4.4.4-13.el6 (x86_64)
glibc-2.12-1.7.el6 (i686)
glibc-2.12-1.7.el6 (x86_64)
glibc-devel-2.12-1.7.el6 (x86_64)
glibc-devel-2.12-1.7.el6.i686
ksh
libgcc-4.4.4-13.el6 (i686)
libgcc-4.4.4-13.el6 (x86_64)
libstdc++-4.4.4-13.el6 (x86_64)
libstdc++-4.4.4-13.el6.i686
libstdc++-devel-4.4.4-13.el6 (x86_64)
libstdc++-devel-4.4.4-13.el6.i686
libaio-0.3.107-10.el6 (x86_64)
libaio-0.3.107-10.el6.i686
libaio-devel-0.3.107-10.el6 (x86_64)
libaio-devel-0.3.107-10.el6.i686
make-3.81-19.el6
sysstat-9.0.4-11.el6 (x86_64)
Missing packages are on Centos 7 installation dvd. Other option if you are connected to internet is just use yum install command.

First option – just mount dvd and install missing packages using rpm -Uvh command from directory <mount dvd>/Packages.
In my case the directory is

/run/media/tomasz/CentOS 7 x86_64/Packages
NOTE – I’m using x86_64 version of packages

rpm -Uvh elfutils-libelf-devel*.x86_64.rpm
rpm -Uvh libaio-devel*.x86_64.rpm
rpm -Uvh unixODBC*.x86_64.rpm
rpm -Uvh ksh*.x86_64.rpm
Second option – use yum install command
yum -y install elfutils-libelf-devel
yum -y install libaio-devel
yum -y install unixODBC
yum -y install unixODBC-devel
yum -y install ksh
Create directory structure

yum install elfutils-libelf-devel 

yum -y install elfutils-libelf-devel
yum install gcc-c++
yum install ksh
yum install libaio-devel
yum install libstdc++-devel
yum install unixODBC
yum install unixODBC-devel

mkdir -p /oracle/ora11g
chown oracle:oinstall /oracle/ora11g
chmod 775 /oracle/ora11g
create ORACLE_BASE directory for oracle

mkdir -p /oracle/ora11g
chown oracle:oinstall /oracle/ora11g
chmod 775 /oracle/ora11g
Create ORACLE_HOME directory for oracle

mkdir -p /oracle/ora11g/product/
chown oracle:oinstall -R /oracle/ora11g/product/
Disable secure linux by editing the “/etc/selinux/config” file, making sure the SELINUX flag is set as follows. It requires REBOOT to be effective !!!

SELINUX=permissive
In Centos Linux 7 /tmp data is stored on tmpfs which consumes memory and is too small. To revert it back to storage just run following command and REBOOT machine to be effective.

systemctl mask tmp.mount
Install database software

Let’s start with database software installation as oracle user.

su - oracle

--unzip software 11.2.0.4
unzip p13390677_112040_Linux-x86-64_1of7.zip
unzip p13390677_112040_Linux-x86-64_2of7.zip
--I defined 4 aliases in .bash_profile of user oracle to make 
--administration heaven :)




--run installation from install directory

/home/oracle/database/runInstaller -silent -force -responseFile /home/oracle/db_install.rsp 


/home/oracle/database/runInstaller -record -destinationFile /private/temp/install_oracle11g.rsp 

#安装类型
oracle.install.option=INSTALL_DB_SWONLY
#主机名称
ORACLE_HOSTNAME=hky.dev.centos.com
#安装组
UNIX_GROUP_NAME=oinstall
#INVENTORY目录
INVENTORY_LOCATION=/oracle/oraInventory
#选择语言
SELECTED_LANGUAGES=en,zh_CN
ORACLE_HOME=/oracle/ora11g/product
ORACLE_BASE=/oracle/ora11g
oracle.install.db.InstallEdition=SE
oracle.install.db.isCustomInstall=true
oracle.install.db.DBA_GROUP=dba
oracle.install.db.OPER_GROUP=oinstall
#数据库类型
oracle.install.db.config.starterdb.type=GENERAL_PURPOSE
oracle.install.db.config.starterdb.globalDBName=ora11g
oracle.install.db.config.starterdb.SID=ora11g
#自动管理内存的最小内存(M)
oracle.install.db.config.starterdb.memoryLimit=512
#设定所有数据库用户使用同一个密码
oracle.install.db.config.starterdb.password.ALL=sys
#设置安全更新必须设置为true,否会提示email地址没有设置不能安装
DECLINE_SECURITY_UPDATES=true


listener configuration
cp /home/oracle/database/response/netca.rsp  /home/oracle/netca.rsp
export DISPLAY=192.168.137.132:0.0
$ORACLE_HOME/bin/netca -silent -responsefile /home/oracle/netca.rsp

Running Database Configuration Assistant in Response File Mode
cp /home/oracle/database/response/dbca.rsp /home/oracle/dbca.rsp
export DISPLAY=192.168.137.132:0.0
$ORACLE_HOME/bin/dbca  -silent -responseFile /home/oracle/dbca.rsp






Question: I want to re-name my database to change the ORACLE_SID value.  I have changed the instance_name parameter in parameter file also but its still at database said showing same when we select instance_name from v$instance?  What is the proper way to re-name an Oracle instance?

Answer:  To completely re-name a database you need to change all of the components where the instance name is located:

    External files: sqlnet.ora, tnsnames.ora, init.ora (spfile)

    Internal locations:  Data dictionary

Here are the "traditional" steps to re-name an Oracle database (note new procedure for renaming an instance in 9i and beyond later on this page):

STEP 1: On the old system, go into SQL*Plus, sign on as SYSDBA and issue: ?alter database backup controlfile to trace?. This will put the create database syntax in the trace file directory. The trace keyword tells oracle to generate a script containing a create controlfile command and store it in the trace directory identified in the user_dump_dest parameter of the init.ora file. It will look something like this:

    STARTUP NOMOUNT
    CREATE CONTROLFILE REUSE DATABASE "OLDLSQ" NORESETLOGS
    NOARCHIVELOG
    MAXLOGFILES 16
    MAXLOGMEMBERS 2
    MAXDATAFILES 240
    MAXINSTANCES 1
    MAXLOGHISTORY 113
    LOGFILE
    GROUP 1 ('/u03/oradata/oldlsq/log1a.dbf',
    '/u03/oradata/olslsq/log1b.dbf') SIZE 30M,
    GROUP 2 ('/u04/oradata/oldlsq/log2a.dbf',
    '/u04/oradata/oldlsq/log2b.dbf') SIZE 30M
    DATAFILE
    '/u01/oradata/oldlsq/system01.dbf',
    '/u01/oradata/oldlsq/mydatabase.dbf'
    ;
    # Recovery is required if any of the datafiles are restored
    # backups, or if the last shutdown was not normal or immediate.
    RECOVER DATABASE
    # Database can now be opened normally.
    ALTER DATABASE OPEN;
     

STEP 2: Shutdown the old database

STEP 3: Change all references to the old instance name in all locations for sqlnet.ora, protocol.ora, tnsnames.ora and the init.ora (or spfile for the database).

STEP 4: Change the database name in the file to reference the new ORACLE_SID instance name:

    STARTUP NOMOUNT
    CREATE CONTROLFILE REUSE DATABASE "NEWLSQ" NORESETLOGS
    NOARCHIVELOG
    MAXLOGFILES 16
    MAXLOGMEMBERS 2
    MAXDATAFILES 240
    MAXINSTANCES 1
    MAXLOGHISTORY 113
    LOGFILE
    GROUP 1 ('/u03/oradata/newlsq/log1a.dbf',
    '/u03/oradata/newlsq/log1b.dbf') SIZE 30M,
    GROUP 2 ('/u04/oradata/newlsq/log2a.dbf',
    '/u04/oradata/newlsq/log2b.dbf') SIZE 30M
    DATAFILE
    '/u01/oradata/newlsq/system01.dbf',
    '/u01/oradata/newlsq/mydatabase.dbf'
    ;
    # Re-named database can now be opened normally.
    ALTER DATABASE OPEN RESETLOGS;
    ALTER TABLESPACE TEMP ADD TEMPFILE ''/u04/oradata/newlsq/log2a.dbf/temp.dbf'
    SIZE 104857600 REUSE AUTOEXTEND OFF;
     

A new method for a database rename instance

For Oracle9i and beyond, Oracle author Dr. Tim Hall has this procedure to rename an Oracle database using the new dbnewid (also called nid, for new ID) utility:

    STEP 1: Backup the database.
     
    STEP 2: Mount the database after a clean shutdown:

        SHUTDOWN IMMEDIATE
        STARTUP MOUNT

    STEP 3: Invoke the DBNEWID utility (nid) specifying the new DBNAME from the command line using a user with SYSDBA privilege:

        nid TARGET=sys/password@TSH1 DBNAME=TSH2

    Assuming the validation is successful the utility prompts for confirmation before performing the actions. Typical output may look something like:

        C:\oracle\920\bin>nid TARGET=sys/password@TSH1 DBNAME=TSH2
        DBNEWID: Release 9.2.0.3.0 - Production
        Copyright (c) 1995, 2002, Oracle Corporation.  All rights reserved.

        Connected to database TSH1 (DBID=1024166118)

        Control Files in database:
            C:\ORACLE\ORADATA\TSH1\CONTROL01.CTL
            C:\ORACLE\ORADATA\TSH1\CONTROL02.CTL
            C:\ORACLE\ORADATA\TSH1\CONTROL03.CTL

        Change database ID and database name TSH1 to TSH2? (Y/[N]) => Y

        Proceeding with operation
        Changing database ID from 1024166118 to 1317278975
        Changing database name from TSH1 to TSH2
            Control File C:\ORACLE\ORADATA\TSH1\CONTROL01.CTL - modified
            Control File C:\ORACLE\ORADATA\TSH1\CONTROL02.CTL - modified
            Control File C:\ORACLE\ORADATA\TSH1\CONTROL03.CTL - modified
            Datafile C:\ORACLE\ORADATA\TSH1\SYSTEM01.DBF - dbid changed, wrote new name
            Datafile C:\ORACLE\ORADATA\TSH1\UNDOTBS01.DBF - dbid changed, wrote new name
            Datafile C:\ORACLE\ORADATA\TSH1\CWMLITE01.DBF - dbid changed, wrote new name
            Control File C:\ORACLE\ORADATA\TSH1\CONTROL01.CTL - dbid changed, wrote new name
            Control File C:\ORACLE\ORADATA\TSH1\CONTROL02.CTL - dbid changed, wrote new name
            Control File C:\ORACLE\ORADATA\TSH1\CONTROL03.CTL - dbid changed, wrote new name

        Database name changed to TSH2.
        Modify parameter file and generate a new password file before restarting.
        Database ID for database TSH2 changed to 1317278975.
        All previous backups and archived redo logs for this database are unusable.
        Shut down database and open with RESETLOGS option.
        Succesfully changed database name and ID.
        DBNEWID - Completed succesfully.

    STEP 4: Shutdown the database:

        SHUTDOWN IMMEDIATE

    STEP 5: Modify the DB_NAME parameter in the initialization parameter file. The startup will result in an error but proceed anyway.

        STARTUP MOUNT
        ALTER SYSTEM SET DB_NAME=TSH2 SCOPE=SPFILE;
        SHUTDOWN IMMEDIATE

    STEP 6: Create a new password file:

        orapwd file=c:\oracle\920\database\pwdTSH2.ora password=password entries=10

    STEP 7: Rename the SPFILE to match the new DBNAME.
     
    STEP 8: If you are using Windows you must recreate the service so the correct name and parameter file are used:
     

        oradim -delete -sid TSH1
        oradim -new -sid TSH2 -intpwd password -startmode a -pfile c:\oracle\920\database\spfileTSH2.ora

    If you are using UNIX/Linux simply reset the ORACLE_SID environment variable:
     

        ORACLE_SID=TSH2; export ORACLE_SID

    STEP 9: Alter the listener.ora and tnsnames.ora setting to match the new database name and restart the listener:
     

        lsnrctl reload

    STEP 10: Open the database with RESETLOGS:
     

        STARTUP MOUNT
        ALTER DATABASE OPEN RESETLOGS;

    STEP 11: Backup the database.


	
oracle autostart stop in linux:
#!/bin/sh
#
# /etc/rc.d/init.d/oracle
# Description: Starts and stops the Oracle database and listeners
# See how we were called.
case "$1" in
  start)
        echo -n "Starting Oracle Databases: "
        echo "----------------------------------------------------" >> /var/log/oracle
        date +"! %T %a %D : Starting Oracle Databases as part of system up." >> /var/log/oracle
        echo "----------------------------------------------------" >> /var/log/oracle
        su - oracle -c dbstart >> /var/log/oracle
        echo "Done."
        echo -n "Starting Oracle Listeners: "
        su - oracle -c "lsnrctl start" >> /var/log/oracle
        echo "Done."
        echo ""
        echo "----------------------------------------------------" >> /var/log/oracle
        date +"! %T %a %D : Finished." >> /var/log/oracle
        echo "----------------------------------------------------" >> /var/log/oracle
        touch /var/lock/subsys/oracle
        ;;
  stop)
        echo -n "Shutting Down Oracle Listeners: "
        echo "----------------------------------------------------" >> /var/log/oracle
        date +"! %T %a %D : Shutting Down Oracle Databases as part of system down." >> /var/log/oracle
        echo "----------------------------------------------------" >> /var/log/oracle
        su - oracle -c "lsnrctl stop" >> /var/log/oracle
        echo "Done."
        rm -f /var/lock/subsys/oracle
        echo -n "Shutting Down Oracle Databases: "
        su - oracle -c dbshut >> /var/log/oracle
        echo "Done."
        echo ""
        echo "----------------------------------------------------" >> /var/log/oracle
        date +"! %T %a %D : Finished." >> /var/log/oracle
        echo "----------------------------------------------------" >> /var/log/oracle
        ;;
  restart)
        echo -n "Restarting Oracle Databases: "
        echo "----------------------------------------------------" >> /var/log/oracle
        date +"! %T %a %D : Restarting Oracle Databases as part of system up." >> /var/log/oracle
        echo "----------------------------------------------------" >> /var/log/oracle
        su - oracle -c dbstop >> /var/log/oracle
        su - oracle -c dbstart >> /var/log/oracle
        echo "Done."
        echo -n "Restarting Oracle Listeners: "
        su - oracle -c "lsnrctl stop" >> /var/log/oracle
        su - oracle -c "lsnrctl start" >> /var/log/oracle
        echo "Done."
        echo ""
        echo "----------------------------------------------------" >> /var/log/oracle
        date +"! %T %a %D : Finished." >> /var/log/oracle
        echo "----------------------------------------------------" >> /var/log/oracle
        touch /var/lock/subsys/oracle
        ;;
  *)
        echo "Usage: oracle {start|stop|restart}"
        exit 1
esac


The following commands will ensure that the databases will come up in runlevels 2,3 and 4:

    $ ln -s ../init.d/oracle /etc/rc.d/rc2.d/S99oracle
    $ ln -s ../init.d/oracle /etc/rc.d/rc3.d/S99oracle
    $ ln -s ../init.d/oracle /etc/rc.d/rc4.d/S99oracle

To stop the databases on reboot or restart we need the following links:

    $ ln -s ../init.d/oracle /etc/rc.d/rc0.d/K01oracle          # Halting
    $ ln -s ../init.d/oracle /etc/rc.d/rc6.d/K01oracle          # Rebooting

	
password:
orapwd file=orapw$ORACLE_SID password=sys entries=20


sqlplus sys/sys as sysdba
show parameter remote

select * from v$psfile_users;
grant sysdba to sys;

