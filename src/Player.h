#pragma once

#ifndef  PLAYER_H_
#define  PLAYER_H_

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QObject>
#include <iostream>

class Player : public QObject {
 Q_OBJECT
 public:
  Player(QObject* o, QString name, QNetworkAccessManager* nam, QString server)
      : name_(name), nam_(nam), server_(server) {}

 private:
  void playColumn(QString name, int column) const {
    QNetworkRequest request(QUrl(server_ + "/api/v1/players/games/" + gameId_));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    nam_->post(request, QString(R"({"playerId":"%1", "column":%2})").arg(name).arg(column).toUtf8());
  }

  void getGame() const {
    QNetworkRequest request(QUrl(server_ + "/api/v1/players/games/" + gameId_));
    nam_->get(request);
  }

  void printBoard(QJsonValue board) const {
    auto rows = board.toArray();
    for (auto row : rows) {
      for (auto cell : row.toArray()) {
        auto cellcontent = cell.toString();
        if (cellcontent == "EMPTY") std::cout << " .";
        else if (cellcontent == "RED") std::cout << " x";
        else if (cellcontent == "YELLOW") std::cout << " o";
      }
      std::cout << "\n";
    }
  }

 public slots:
  void onResponse(QNetworkReply* reply) {
    reply->deleteLater();
    auto content = reply->readAll();
    std::cout << content.toStdString() << std::endl;
    QJsonParseError error;
    auto document = QJsonDocument::fromJson(content, &error);
    auto object = document.object();
    if (object.contains("gameId")) {
      gameId_ = object["gameId"].toString();
      getGame();
      return;
    }
    if (object["finished"].toBool()) {
      QNetworkRequest request(QUrl(server_ + "/api/v1/players/join"));
      request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
      auto reply = nam_->post(request, QString(R"({"playerId":"%1"})").arg(name_).toUtf8());
    }
    if (object["currentPlayerId"] == name_) {
      printBoard(object["board"]);
      playColumn(name_, col_);
      col_ = (col_ + 1) % 7;
    } else {
      if (true) {
        // In demo play for other player as well
        playColumn("Gugus", col_);
      } else {
        getGame();
      }
    }
  };

 private:
  QString name_;
  QNetworkAccessManager* nam_;
  QString gameId_;
  int col_ = 0;
  QString server_;
};

#endif // PLAYER_H_
