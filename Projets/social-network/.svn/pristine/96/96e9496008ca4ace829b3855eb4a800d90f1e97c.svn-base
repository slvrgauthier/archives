DROP TABLE IF EXISTS chat_favoris;
DROP TABLE IF EXISTS chat_conversation;
DROP TABLE IF EXISTS chat_message;

-- Table contenant tous les favoris
CREATE TABLE IF NOT EXISTS chat_favoris (
  id_favoris        SERIAL          PRIMARY KEY,
  id_utilisateur    BIGINT(20) UNSIGNED             NOT NULL,
  id_contact        BIGINT(20) UNSIGNED             NOT NULL,
  CONSTRAINT FK_user_fav1 FOREIGN KEY (id_utilisateur) REFERENCES user (id_u),
  CONSTRAINT FK_user_fav2 FOREIGN KEY (id_contact) REFERENCES user (id_u)
) ENGINE=InnoDB,DEFAULT CHARSET=utf8;

-- Table contenant toutes les conversations
CREATE TABLE IF NOT EXISTS chat_conversation (
  id_conversation   int UNSIGNED                    NOT NULL, /* ni primary, ni serial sinon 1 seul membre */
  id_membre         BIGINT(20) UNSIGNED             NOT NULL,
  PRIMARY KEY (id_conversation,id_membre),
  CONSTRAINT FK_user_conv FOREIGN KEY (id_membre) REFERENCES user (id_u)
) ENGINE=InnoDB,DEFAULT CHARSET=utf8;


-- Table contenant tous les messages
CREATE TABLE IF NOT EXISTS chat_message (
  id_message        SERIAL          PRIMARY KEY,
  id_conversation   int UNSIGNED             NOT NULL,
  id_source         BIGINT(20) UNSIGNED             NOT NULL,
  message           TEXT            NOT NULL,
  date_envoi        datetime        NOT NULL,
  /*CONSTRAINT FK_user_msg1 FOREIGN KEY (id_conversation) REFERENCES chat_conversation (id_conversation),*/
  CONSTRAINT FK_user_msg2 FOREIGN KEY (id_source) REFERENCES user (id_u)
) ENGINE=InnoDB,DEFAULT CHARSET=utf8;