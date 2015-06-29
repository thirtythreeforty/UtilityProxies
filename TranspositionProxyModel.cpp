/**
    TranspositionProxyModel.cpp
    Copyright (C) 2015 George Hilliard

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

#include "TranspositionProxyModel.h"

static Qt::Orientation swapOrientation(Qt::Orientation orientation)
{
    return orientation == Qt::Vertical ? Qt::Horizontal : Qt::Vertical;
}

TranspositionProxyModel::TranspositionProxyModel(QObject *parent)
    : QAbstractProxyModel(parent)
    , d_ptr(0) // not needed
{}

QModelIndex TranspositionProxyModel::index(int row, int column, const QModelIndex& parent) const
{
    Q_UNUSED(parent);
    return createIndex(row, column);
}

QModelIndex TranspositionProxyModel::parent(const QModelIndex& child) const
{
    Q_UNUSED(child);
    return QModelIndex();
}

int TranspositionProxyModel::rowCount(const QModelIndex& parent) const
{
    if(!sourceModel())
        return 0;
    return sourceModel()->columnCount(mapToSource(parent));
}

int TranspositionProxyModel::columnCount(const QModelIndex& parent) const
{
    if(!sourceModel())
        return 0;
    return sourceModel()->rowCount(mapToSource(parent));
}

QVariant TranspositionProxyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(!sourceModel())
        return QVariant();
    return sourceModel()->headerData(section, swapOrientation(orientation), role);
}

void TranspositionProxyModel::setSourceModel(QAbstractItemModel* newSourceModel)
{
    QAbstractItemModel* oldSourceModel = sourceModel();

    if(oldSourceModel) {
        disconnect(oldSourceModel, &QAbstractItemModel::columnsAboutToBeInserted,
                   this,           &TranspositionProxyModel::handle_columnsAboutToBeInserted);
        disconnect(oldSourceModel, &QAbstractItemModel::columnsInserted,
                   this,           &TranspositionProxyModel::handle_columnsInserted);
        disconnect(oldSourceModel, &QAbstractItemModel::columnsAboutToBeMoved,
                   this,           &TranspositionProxyModel::handle_columnsAboutToBeMoved);
        disconnect(oldSourceModel, &QAbstractItemModel::columnsMoved,
                   this,           &TranspositionProxyModel::handle_columnsMoved);
        disconnect(oldSourceModel, &QAbstractItemModel::columnsAboutToBeRemoved,
                   this,           &TranspositionProxyModel::handle_columnsAboutToBeRemoved);
        disconnect(oldSourceModel, &QAbstractItemModel::columnsRemoved,
                   this,           &TranspositionProxyModel::handle_columnsRemoved);

        disconnect(oldSourceModel, &QAbstractItemModel::rowsAboutToBeInserted,
                   this,           &TranspositionProxyModel::handle_rowsAboutToBeInserted);
        disconnect(oldSourceModel, &QAbstractItemModel::rowsInserted,
                   this,           &TranspositionProxyModel::handle_rowsInserted);
        disconnect(oldSourceModel, &QAbstractItemModel::rowsAboutToBeMoved,
                   this,           &TranspositionProxyModel::handle_rowsAboutToBeMoved);
        disconnect(oldSourceModel, &QAbstractItemModel::rowsMoved,
                   this,           &TranspositionProxyModel::handle_rowsMoved);
        disconnect(oldSourceModel, &QAbstractItemModel::rowsAboutToBeRemoved,
                   this,           &TranspositionProxyModel::handle_rowsAboutToBeRemoved);
        disconnect(oldSourceModel, &QAbstractItemModel::rowsRemoved,
                   this,           &TranspositionProxyModel::handle_rowsRemoved);

        disconnect(oldSourceModel, &QAbstractItemModel::dataChanged,
                   this,           &TranspositionProxyModel::handle_dataChanged);
        disconnect(oldSourceModel, &QAbstractItemModel::headerDataChanged,
                   this,           &TranspositionProxyModel::handle_headerDataChanged);
        disconnect(oldSourceModel, &QAbstractItemModel::layoutAboutToBeChanged,
                   this,           &TranspositionProxyModel::handle_layoutAboutToBeChanged);
        disconnect(oldSourceModel, &QAbstractItemModel::layoutChanged,
                   this,           &TranspositionProxyModel::handle_layoutChanged);

        disconnect(oldSourceModel, &QAbstractItemModel::modelAboutToBeReset,
                   this,           &TranspositionProxyModel::handle_modelAboutToBeReset);
        disconnect(oldSourceModel, &QAbstractItemModel::modelReset,
                   this,           &TranspositionProxyModel::handle_modelReset);
    }

    QAbstractProxyModel::setSourceModel(newSourceModel);

    if(newSourceModel) {
        connect(newSourceModel, &QAbstractItemModel::columnsAboutToBeInserted,
                this,           &TranspositionProxyModel::handle_columnsAboutToBeInserted);
        connect(newSourceModel, &QAbstractItemModel::columnsInserted,
                this,           &TranspositionProxyModel::handle_columnsInserted);
        connect(newSourceModel, &QAbstractItemModel::columnsAboutToBeMoved,
                this,           &TranspositionProxyModel::handle_columnsAboutToBeMoved);
        connect(newSourceModel, &QAbstractItemModel::columnsMoved,
                this,           &TranspositionProxyModel::handle_columnsMoved);
        connect(newSourceModel, &QAbstractItemModel::columnsAboutToBeRemoved,
                this,           &TranspositionProxyModel::handle_columnsAboutToBeRemoved);
        connect(newSourceModel, &QAbstractItemModel::columnsRemoved,
                this,           &TranspositionProxyModel::handle_columnsRemoved);

        connect(newSourceModel, &QAbstractItemModel::rowsAboutToBeInserted,
                this,           &TranspositionProxyModel::handle_rowsAboutToBeInserted);
        connect(newSourceModel, &QAbstractItemModel::rowsInserted,
                this,           &TranspositionProxyModel::handle_rowsInserted);
        connect(newSourceModel, &QAbstractItemModel::rowsAboutToBeMoved,
                this,           &TranspositionProxyModel::handle_rowsAboutToBeMoved);
        connect(newSourceModel, &QAbstractItemModel::rowsMoved,
                this,           &TranspositionProxyModel::handle_rowsMoved);
        connect(newSourceModel, &QAbstractItemModel::rowsAboutToBeRemoved,
                this,           &TranspositionProxyModel::handle_rowsAboutToBeRemoved);
        connect(newSourceModel, &QAbstractItemModel::rowsRemoved,
                this,           &TranspositionProxyModel::handle_rowsRemoved);

        connect(newSourceModel, &QAbstractItemModel::dataChanged,
                this,           &TranspositionProxyModel::handle_dataChanged);
        connect(newSourceModel, &QAbstractItemModel::headerDataChanged,
                this,           &TranspositionProxyModel::handle_headerDataChanged);
        connect(newSourceModel, &QAbstractItemModel::layoutAboutToBeChanged,
                this,           &TranspositionProxyModel::handle_layoutAboutToBeChanged);
        connect(newSourceModel, &QAbstractItemModel::layoutChanged,
                this,           &TranspositionProxyModel::handle_layoutChanged);

        connect(newSourceModel, &QAbstractItemModel::modelAboutToBeReset,
                this,           &TranspositionProxyModel::handle_modelAboutToBeReset);
        connect(newSourceModel, &QAbstractItemModel::modelReset,
                this,           &TranspositionProxyModel::handle_modelReset);
    }
}

QModelIndex TranspositionProxyModel::mapToSource(const QModelIndex& proxyIndex) const
{
    if(!sourceModel())
        return QModelIndex();
    return sourceModel()->index(proxyIndex.column(), proxyIndex.row());
}

QModelIndex TranspositionProxyModel::mapFromSource(const QModelIndex& sourceIndex) const
{
    if(!sourceModel())
        return QModelIndex();
    return index(sourceIndex.column(), sourceIndex.row(), QModelIndex());
}

void TranspositionProxyModel::handle_columnsAboutToBeInserted(QModelIndex parent, int first, int last)
{
    beginInsertRows(mapFromSource(parent), first, last);
}

void TranspositionProxyModel::handle_columnsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    endInsertRows();
}

void TranspositionProxyModel::handle_columnsAboutToBeMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn)
{
    beginMoveRows(mapFromSource(sourceParent), sourceStart, sourceEnd, mapFromSource(destinationParent), destinationColumn);
}

void TranspositionProxyModel::handle_columnsMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn)
{
    Q_UNUSED(sourceParent);
    Q_UNUSED(sourceStart);
    Q_UNUSED(sourceEnd);
    Q_UNUSED(destinationParent);
    Q_UNUSED(destinationColumn);
    endMoveRows();
}

void TranspositionProxyModel::handle_columnsAboutToBeRemoved(QModelIndex parent, int first, int last)
{
    beginRemoveRows(mapFromSource(parent), first, last);
}

void TranspositionProxyModel::handle_columnsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    endRemoveRows();
}

void TranspositionProxyModel::handle_rowsAboutToBeInserted(QModelIndex parent, int first, int last)
{
    beginInsertColumns(mapFromSource(parent), first, last);
}

void TranspositionProxyModel::handle_rowsInserted(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    endInsertColumns();
}

void TranspositionProxyModel::handle_rowsAboutToBeMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn)
{
    beginMoveColumns(mapFromSource(sourceParent), sourceStart, sourceEnd, destinationParent, destinationColumn);
}

void TranspositionProxyModel::handle_rowsMoved(QModelIndex sourceParent, int sourceStart, int sourceEnd, QModelIndex destinationParent, int destinationColumn)
{
    Q_UNUSED(sourceParent);
    Q_UNUSED(sourceStart);
    Q_UNUSED(sourceEnd);
    Q_UNUSED(destinationParent);
    Q_UNUSED(destinationColumn);
    endMoveColumns();
}

void TranspositionProxyModel::handle_rowsAboutToBeRemoved(QModelIndex parent, int first, int last)
{
    beginRemoveColumns(mapFromSource(parent), first, last);
}

void TranspositionProxyModel::handle_rowsRemoved(QModelIndex parent, int first, int last)
{
    Q_UNUSED(parent);
    Q_UNUSED(first);
    Q_UNUSED(last);
    endRemoveColumns();
}

void TranspositionProxyModel::handle_dataChanged(QModelIndex topLeft, QModelIndex bottomRight, QVector<int> roles)
{
    Q_EMIT dataChanged(mapFromSource(topLeft), mapFromSource(bottomRight), roles);
}

void TranspositionProxyModel::handle_headerDataChanged(Qt::Orientation orientation, int first, int last)
{
    Q_EMIT headerDataChanged(swapOrientation(orientation), first, last);
}

void TranspositionProxyModel::handle_layoutAboutToBeChanged(QList<QPersistentModelIndex> parents, QAbstractItemModel::LayoutChangeHint hint)
{
    QList<QPersistentModelIndex> proxyParents;
    proxyParents.reserve(parents.size());
    for(QList<QPersistentModelIndex>::const_iterator it = parents.cbegin(); it != parents.cend(); ++it) {
        proxyParents.append(mapFromSource(*it));
    }
    Q_EMIT layoutAboutToBeChanged(proxyParents, hint);
}

void TranspositionProxyModel::handle_layoutChanged(QList<QPersistentModelIndex> parents, QAbstractItemModel::LayoutChangeHint hint)
{
    QList<QPersistentModelIndex> proxyParents;
    proxyParents.reserve(parents.size());
    for(QList<QPersistentModelIndex>::const_iterator it = parents.cbegin(); it != parents.cend(); ++it) {
        proxyParents.append(mapFromSource(*it));
    }
    Q_EMIT layoutChanged(proxyParents, hint);
}

void TranspositionProxyModel::handle_modelAboutToBeReset()
{
    beginResetModel();
}

void TranspositionProxyModel::handle_modelReset()
{
    endResetModel();
}
