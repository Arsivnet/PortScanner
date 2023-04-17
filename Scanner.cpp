#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <QApplication>
#include <QSpinBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QMessageBox>


void scanPorts(const char*, int, int);


int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
	
	QWidget *window = new QWidget;
	QGridLayout *grid = new QGridLayout(window);
	//QHBoxLayout *hbox = new QHBoxLayout(grid);


	QLabel *label = new QLabel("Domain name:");
	QLabel *startlbl = new QLabel("Start");
	QLabel *endlbl = new QLabel("End");
    QLineEdit *domain = new QLineEdit();
	QSpinBox *startPort = new QSpinBox();
	QSpinBox *endPort = new QSpinBox();
	QPushButton *scanbtn = new QPushButton("Scan");
	
	startPort->setRange(0,100000);
	endPort->setRange(0,100000);

	QObject::connect(scanbtn, &QPushButton::clicked, [=]{scanPorts(domain->text().toUtf8().constData(), startPort->value(), endPort->value());});

	grid->addWidget(label, 0, 0, Qt::AlignRight);
	grid->addWidget(domain, 0, 1, Qt::AlignLeft);
	grid->addWidget(startlbl, 1, 0, Qt::AlignBottom);
	grid->addWidget(endlbl, 1, 1, Qt::AlignBottom);
	grid->addWidget(startPort, 2, 0, Qt::AlignTop);
	grid->addWidget(endPort, 2, 1, Qt::AlignTop);
	grid->addWidget(scanbtn, 3, 0, Qt::AlignTop);

	window->show();
	return app.exec();

}


void scanPorts(const char* domain, int startPort, int endPort){
	
	if(*domain == 0){
	QMessageBox msgBox;
	msgBox.setText("Please enter a domain");
	msgBox.setIcon(QMessageBox::Warning);
	msgBox.exec();
	return;
	}

    struct addrinfo hints; //hints basically determines which sockets get to be in res.
    struct addrinfo *res; //sockets we get from getaddrinfo, restricted by the attributes we specified in hints.
    int sockfd;

    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_INET; //We only want IPV4 sockets in res. So we specify this in hints. Use AF_INET6 for IPV6 and AF_UNSPEC for both.
    hints.ai_socktype = SOCK_STREAM;

    char service[4] = "80"; //Internet service and it's port number. 80 is arbitrary as we're using this variable to convert i to string. But you can type the number or the name of the service you want to check here and it will return the ports associated with that service. Number 80 is for HTTP.
    for(int i = startPort ;i < endPort ;i++)
    {

        sprintf(service, "%d", i);
    
        getaddrinfo(domain, service , &hints, &res);

        sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
        printf("%d portu kontrol ediliyor\n ",i);
        int c = connect(sockfd, res->ai_addr, res->ai_addrlen);

        if(c != -1)
        {
            printf("%d Port açık \n ",i);
        }
        else printf("%d Portu Kapalı \n ",i);
        
    }


}
