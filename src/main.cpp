#include "Player.h"

#include <QCoreApplication>
#include <QNetworkAccessManager>
#include <QNetworkRequest>

QString server = "http://localhost:8080";
QString playerName = "Joe";
QNetworkAccessManager* networkAccessManager;

int main(int argc, char** argv) {
  auto app = new QCoreApplication(argc, argv);
  networkAccessManager = new QNetworkAccessManager{};

  Player player(app, playerName, networkAccessManager, server);

  QNetworkRequest request(QUrl(server + "/api/v1/players/join"));
  request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
  auto reply = networkAccessManager->post(request, QString(R"({"playerId":"%1"})").arg(playerName).toUtf8());

  app->connect(networkAccessManager, &QNetworkAccessManager::finished, &player, &Player::onResponse);

  app->exec();
}