/**
    SubsetProxyModel.cpp
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

#include "SubsetProxyModel.h"

class SubsetProxyModelPrivate {
public:
    SubsetProxyModelPrivate(SubsetProxyModel* parent);
private:
    QPersistentModelIndex _topLeft, _bottomRight;
    bool _boundsValid;

    SubsetProxyModel* const q_ptr;
    Q_DECLARE_PUBLIC(SubsetProxyModel)
};

SubsetProxyModel::SubsetProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
    , d_ptr(new SubsetProxyModelPrivate(this))
{}

bool SubsetProxyModel::filterAcceptsRow(int source_row, const QModelIndex& source_parent) const
{
    Q_D(const SubsetProxyModel);

    return d->_boundsValid
            && source_row >= d->_topLeft.row()
            && source_row <= d->_bottomRight.row()
            && !source_parent.isValid();
}

bool SubsetProxyModel::filterAcceptsColumn(int source_column, const QModelIndex& source_parent) const
{
    Q_D(const SubsetProxyModel);

    return d->_boundsValid &&
            source_column >= d->_topLeft.column()
            && source_column <= d->_bottomRight.column()
            && !source_parent.isValid();
}

void SubsetProxyModel::setBounds(const QModelIndex& sourceTopLeft, const QModelIndex& sourceBottomRight)
{
    Q_D(SubsetProxyModel);

    Q_ASSERT(sourceTopLeft.model() == sourceModel());
    Q_ASSERT(sourceBottomRight.model() == sourceModel());

    beginResetModel();

    d->_topLeft = sourceTopLeft;
    d->_bottomRight = sourceBottomRight;
    d->_boundsValid = true;

    endResetModel();

    Q_EMIT boundsChanged(sourceTopLeft, sourceBottomRight);
}

void SubsetProxyModel::setTopLeftBound(const QModelIndex& sourceTopLeft)
{
    Q_D(SubsetProxyModel);

    Q_ASSERT(sourceTopLeft.model() == sourceModel());

    beginResetModel();

    d->_topLeft = sourceTopLeft;

    endResetModel();

    Q_EMIT boundsChanged(sourceTopLeft, d->_bottomRight);
}

void SubsetProxyModel::setBottomRightBound(const QModelIndex& sourceBottomRight)
{
    Q_D(SubsetProxyModel);

    Q_ASSERT(sourceBottomRight.model() == sourceModel());

    beginResetModel();

    d->_bottomRight = sourceBottomRight;

    endResetModel();

    Q_EMIT boundsChanged(d->_topLeft, sourceBottomRight);
}

SubsetProxyModelPrivate::SubsetProxyModelPrivate(SubsetProxyModel* parent)
    : _boundsValid(false)
    , q_ptr(parent)
{}
