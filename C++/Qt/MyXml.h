#ifndef MYXML_H
#define MYXML_H

#include <QtCore/QCoreApplication>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtXml/QDomDocument>

//写xml
void WriteXml() {
    QFile file("test.xml");
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return;

    QDomDocument doc;
    QDomProcessingInstruction instruction;
    instruction = doc.createProcessingInstruction(
        "xml", "version=\"1.0\" encoding=\"UTF-8\"");
    doc.appendChild(instruction);
    QDomElement root = doc.createElement("routine");
    doc.appendChild(root);
    {
        QDomElement routine1 = doc.createElement("routine1");
        QDomElement name = doc.createElement("name");
        QDomText text;
        text = doc.createTextNode("张三");
        name.appendChild(text);
        routine1.appendChild(name);
        QDomElement birthday = doc.createElement("birthday");
        text = doc.createTextNode("10.01");
        birthday.appendChild(text);
        routine1.appendChild(birthday);
        root.appendChild(routine1);
    }

    {
        QDomElement routine2 = doc.createElement("routine2");
        QDomElement name = doc.createElement("name");
        QDomText text;
        text = doc.createTextNode("李四");
        name.appendChild(text);
        routine2.appendChild(name);
        QDomElement birthday = doc.createElement("birthday");
        text = doc.createTextNode("11.11");
        birthday.appendChild(text);
        routine2.appendChild(birthday);
        root.appendChild(routine2);
    }

    QTextStream out_stream(&file);
    doc.save(out_stream, 4);
    file.close();
}

void ReadXml() {
    QFile file("test.xml");
    if (!file.open(QFile::ReadOnly))
        return;

    QDomDocument doc;
    if (!doc.setContent(&file)) {
        file.close();
        return;
    }
    file.close();

    QDomElement root = doc.documentElement();
    qDebug() << root.nodeName();
    QDomNode node = root.firstChild();
    while (!node.isNull()) {
        if (node.isElement()) {
            QDomElement e = node.toElement();
            qDebug() << e.tagName();
            QDomNodeList list = e.childNodes();
            for (int i = 0; i < list.count(); i++) {
                QDomNode n = list.at(i);
                if (node.isElement())
                    qDebug() << n.nodeName() << ":" << n.toElement().text();
            }
        }
        node = node.nextSibling();
    }
}

#endif // MYXML_H