#include <QtGui>

#include "physchalkboard.h"
// #include "arrow.h"

// PhysChalkboard::PhysChalkboard(QMenu *itemMenu, QObject *parent) : QGraphicsScene(parent) {
PhysChalkboard::PhysChalkboard(QObject *parent) : QGraphicsScene(parent) {
     // myItemMenu = itemMenu;
     myMode = MoveItem;
     // myItemType = DiagramItem::Step;
     line = 0;
     textItem = 0;
     myItemColor = Qt::white;
     myTextColor = Qt::black;
     myLineColor = Qt::black;
}

void PhysChalkboard::setLineColor(const QColor &color) {
    /*
    myLineColor = color;
    if (isItemChange(Arrow::Type)) {
        Arrow *item = qgraphicsitem_cast<Arrow *>(selectedItems().first());
        item -> setColor(myLineColor);
        update();
    }
    */
}

void PhysChalkboard::setTextColor(const QColor &color) {
    myTextColor = color;
    /*
    if (isItemChange(DiagramTextItem::Type)) {
        DiagramTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());
        item -> setDefaultTextColor(myTextColor);
    }
    */
}

void PhysChalkboard::setItemColor(const QColor &color) {
    myItemColor = color;
    /*
    if (isItemChange(DiagramItem::Type)) {
        DiagramItem *item = qgraphicsitem_cast<DiagramItem *>(selectedItems().first());
        item -> setBrush(myItemColor);
    }
    */
}

void PhysChalkboard::setFont(const QFont &font) {
    myFont = font;

    /*
    if (isItemChange(DiagramTextItem::Type)) {
        QGraphicsTextItem *item = qgraphicsitem_cast<DiagramTextItem *>(selectedItems().first());

        //At this point the selection can change so the first selected item might not be a DiagramTextItem
        if (item)
            item -> setFont(myFont);
    }
    */
}

void PhysChalkboard::setMode(Mode mode) {
    myMode = mode;
}

/*
void PhysChalkboard::setItemType(DiagramItem::DiagramType type) {
    myItemType = type;
}
*/

void PhysChalkboard::editorLostFocus(CartesianLabel *item) {
    /*
    QTextCursor cursor = item -> textCursor();
    cursor.clearSelection();
    item -> setTextCursor(cursor);

    if (item->toPlainText().isEmpty()) {
        removeItem(item);
        item->deleteLater();
    }
    */
}

void PhysChalkboard::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*
    if (mouseEvent -> button() != Qt::LeftButton)
        return;
    DiagramItem *item;
        switch (myMode) {
        case InsertItem:
            item = new DiagramItem(myItemType, myItemMenu);
            item -> setBrush(myItemColor);
            addItem(item);
            item -> setPos(mouseEvent -> scenePos());
            emit itemInserted(item);
            break;
        case InsertLine:
            line = new QGraphicsLineItem(QLineF(mouseEvent -> scenePos(),
            mouseEvent -> scenePos()));
            line -> setPen(QPen(myLineColor, 2));
            addItem(line);
            break;
        case InsertText:
            textItem = new DiagramTextItem();
            textItem -> setFont(myFont);
            textItem -> setTextInteractionFlags(Qt::TextEditorInteraction);
            textItem -> setZValue(1000.0);
            connect(textItem, SIGNAL(lostFocus(CartesianLabel *)), this, SLOT(editorLostFocus(CartesianLabel *)));
            connect(textItem, SIGNAL(selectedChange(QGraphicsItem *)), this, SIGNAL(itemSelected(QGraphicsItem *)));
            addItem(textItem);
            textItem -> setDefaultTextColor(myTextColor);
            textItem -> setPos(mouseEvent -> scenePos());
            emit textInserted(textItem);
            break;
        default:
            ;
    }
    */
    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PhysChalkboard::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*
    if (myMode == InsertLine && line != 0) {
        QLineF newLine(line -> line().p1(), mouseEvent -> scenePos());
        line -> setLine(newLine);
    }
    else if (myMode == MoveItem) {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }
    */
}

void PhysChalkboard::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) {
    /*
    if (line != 0 && myMode == InsertLine) {
        QList<QGraphicsItem *> startItems = items(line->line().p1());
        if (startItems.count() && startItems.first() == line)
            startItems.removeFirst();
        QList<QGraphicsItem *> endItems = items(line->line().p2());
        if (endItems.count() && endItems.first() == line)
            endItems.removeFirst();

        removeItem(line);
        delete line;

        if (
            startItems.count() > 0 &&
            endItems.count() > 0 &&
            startItems.first()->type() == DiagramItem::Type &&
            endItems.first()->type() == DiagramItem::Type &&
            startItems.first() != endItems.first()) {

            DiagramItem *startItem = qgraphicsitem_cast<DiagramItem *>(startItems.first());
            DiagramItem *endItem = qgraphicsitem_cast<DiagramItem *>(endItems.first());
            Arrow *arrow = new Arrow(startItem, endItem);
            arrow -> setColor(myLineColor);
            startItem -> addArrow(arrow);
            endItem -> addArrow(arrow);
            arrow -> setZValue(-1000.0);
            addItem(arrow);
            arrow -> updatePosition();
        }
    }
    line = 0;
    */
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

bool PhysChalkboard::isItemChange(int type) {
    /*
    foreach (QGraphicsItem *item, selectedItems()) {
        if (item -> type() == type)
            return true;
    }
    */
    return false;
}
