#ifndef MODEL_HPP
#define MODEL_HPP

#include <QAbstractTableModel>
#include <QVector>
#include <QString>
#include "comp.h"

class MyModel1 : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel1(QVector<comp> *data = new QVector<comp>(), QObject *parent = nullptr)
        : QAbstractTableModel(parent), _comp(data) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return _comp->count();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 3;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if(role != Qt::DisplayRole) return QVariant();

        if(orientation == Qt::Horizontal) {
            switch(section) {
            case 0: return tr("Название");
            case 1: return tr("Секция");
            case 2: return tr("Цена");
            default: return QVariant();
            }
        }
        return QString("%1").arg(section + 1);
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if(role != Qt::DisplayRole) return QVariant();

        switch(index.column()) {
        case 0: return (*_comp)[index.row()].name;
        case 1: return (*_comp)[index.row()].section;
        case 2: return (*_comp)[index.row()].price;
        default: return QVariant();
        }
    }

    void setModel(COMP<comp>* comp) {
        beginResetModel();
        _comp->clear();
        for (int i = 0; i < comp->size(); i++) {
            *_comp << comp->at(i);
        }
        endResetModel();
    }

protected:
    QVector<comp>* _comp;
};

class MyModel2 : public QAbstractTableModel
{
    Q_OBJECT
public:
    MyModel2(QVector<bag> *data = new QVector<bag>(), QObject *parent = nullptr)
        : QAbstractTableModel(parent), _bag(data) {}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override {
        return _bag->count();
    }

    int columnCount(const QModelIndex &parent = QModelIndex()) const override {
        return 3;
    }

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override {
        if(role != Qt::DisplayRole) return QVariant();

        if(orientation == Qt::Horizontal) {
            switch(section) {
            case 0: return tr("Название");
            case 1: return tr("Секция");
            case 2: return tr("Количество");
            default: return QVariant();
            }
        }
        return QString("%1").arg(section + 1);
    }

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override {
        if(role != Qt::DisplayRole) return QVariant();

        switch(index.column()) {
        case 0: return (*_bag)[index.row()].name;
        case 1: return (*_bag)[index.row()].section;
        case 2: return (*_bag)[index.row()].num;
        default: return QVariant();
        }
    }

    void setModel(COMP<bag>* bag) {
        beginResetModel();
        _bag->clear();
        for (int i = 0; i < bag->size(); i++) {
            *_bag << bag->at(i);
        }
        endResetModel();
    }

protected:
    QVector<bag>* _bag;
};

#endif // MODEL_HPP
