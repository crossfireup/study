# introduction

# common use

  - create a database
    ```
    create user dolphin with password "helloc2017" login;
    create database msf3 owner dolphin;
    alter role dolphin with password 'helloc2017';

    grant all on DATABASE msf3 to dolphin;

    alter user dolphin login;

    vim /etc/postgresql/9.5/main/pg_hba.conf
    local   all             all                                     trust

  - login
    ``` 
    pgsql -U dolphin -W -d msf3
    ```