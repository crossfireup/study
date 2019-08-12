# golang
    - [go]https://golang.org/cmd/go/
    - [go src](https://github.com/golang/go)

# basic
    - go
        ```
        export GOPATH=$HOME/go/src/
        git clone https://github.com/golang/go.git $GOPATH
        go build
        go run
        go install
        go build -gcflags=-S main.go
        go test
        # IR
        ssadump -build FS main.go
        go tool vet -shadow
        ```

# docker
    - cmd
        '''
        "screen ~/Library/Containers/com.docker.docker/Data/vms/0/tty"
        resize
        stty rows 50 cols 132
        docker inspect --format '{{.State.Pid}}'
        curl -XGET https://raw.githubusercontent.com/docker/cli/master/contrib/completion/bash/docker > $(brew --prefix)/etc/bash_completion.d/docker
        '''

# kubernetes
    - proxy config
        '''
        https://github.com/kubernetes/minikube/blob/master/docs/http_proxy.md
        '''

    - error dashboard[https://github.com/kubernetes/minikube/issues/3493]
        '''
        kubectl create clusterrolebinding kube-system-cluster-admin --clusterrole=cluster-admin --serviceaccount=kube-system:default
        clusterrolebinding.rbac.authorization.k8s.io/kube-system-cluster-admin created
        kubectl delete -n kube-system pods kubernetes-dashboard-7b8ddcb5d6-m8gs9
        kubectl get pods --namespace=kube-system
        '''

    - download proxy
        '''conf
        scrub-anchor "com.apple/*"
        nat-anchor "com.apple/*"
        rdr-anchor "com.apple/*"
        rdr pass inet proto tcp from 192.168.99.105 to any port 50403 -> 127.0.0.1 port 50403
        dummynet-anchor "com.apple/*" 
        '''

        '''
        sudo pfctl -vnf /etc/pf.conf
        sudo pfctl -ef /etc/pf.conf
        sudo pfctl -s nat
        '''

