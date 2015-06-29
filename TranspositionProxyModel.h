/**
    TranspositionProxyModel.h
    Copyright (C) 2015 George Hilliard

    TranspositionProxyModel is part of the UtilityProxies library.
    See <https://www.github.com/thirtythreeforty/UtilityProxies> for support.

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef TRANSPOSITIONPROXYMODEL_H
#define TRANSPOSITIONPROXYMODEL_H

#include <QAbstractProxyModel>

#include "utilityproxies_global.h"

class TranspositionProxyModelPrivate;

class UTILITYPROXIESSHARED_EXPORT TranspositionProxyModel : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit TranspositionProxyModel(QObject *parent = 0);

    virtual QModelIndex index(int row, int column, const QModelIndex& parent) const;
    virtual QModelIndex parent(const QModelIndex& child) const;
    virtual int rowCount(const QModelIndex& parent) const;
    virtual int columnCount(const QModelIndex& parent) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;

    virtual void setSourceModel(QAbstractItemModel* newSourceModel);
    virtual QModelIndex mapToSource(const QModelIndex& proxyIndex) const;
    virtual QModelIndex mapFromSource(const QModelIndex& sourceIndex) const;

private Q_SLOTS:
    void handle_columnsAboutToBeInserted(QModelIndex parent, int first, int last);
    void handle_columnsInserted(QModelIndex parent, int first, int last);
    void handle_columnsAboutToBeMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn);
    void handle_columnsMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn);
    void handle_columnsAboutToBeRemoved(QModelIndex parent, int first, int last);
    void handle_columnsRemoved(QModelIndex parent, int first, int last);

    void handle_rowsAboutToBeInserted(QModelIndex parent, int first, int last);
    void handle_rowsInserted(QModelIndex parent, int first, int last);
    void handle_rowsAboutToBeMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn);
    void handle_rowsMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn);
    void handle_rowsAboutToBeRemoved(QModelIndex parent, int first, int last);
    void handle_rowsRemoved(QModelIndex parent, int first, int last);

    void handle_dataChanged(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles);
    void handle_headerDataChanged(Qt::Orientation orientation, int first, int last);

    void handle_layoutAboutToBeChanged(QList<QPersistentModelIndex> parents, QAbstractItemModel::LayoutChangeHint hint);
    void handle_layoutChanged(QList<QPersistentModelIndex> parents, QAbstractItemModel::LayoutChangeHint hint);

    void handle_modelAboutToBeReset();
    void handle_modelReset();

private:
    TranspositionProxyModelPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(TranspositionProxyModel)
};

#endif // TRANSPOSITIONPROXYMODEL_H
