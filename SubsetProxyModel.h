/**
    SubsetProxyModel.h
    Copyright (C) 2015 George Hilliard

    SubsetProxyModel is part of the UtilityProxies library.
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

#ifndef SUBSETPROXYMODEL_H
#define SUBSETPROXYMODEL_H

#include <QSortFilterProxyModel>

#include "utilityproxies_global.h"

class SubsetProxyModelPrivate;

class UTILITYPROXIESSHARED_EXPORT SubsetProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SubsetProxyModel(QObject *parent = 0);

Q_SIGNALS:
    void boundsChanged(const QModelIndex& sourceTopLeft, const QModelIndex& sourceBottomRight);

public Q_SLOTS:
    void setBounds(const QModelIndex& sourceTopLeft, const QModelIndex& sourceBottomRight);
    void setTopLeftBound(const QModelIndex& sourceTopLeft);
    void setBottomRightBound(const QModelIndex& sourceBottomRight);

protected:
    virtual bool filterAcceptsRow(int source_row, const QModelIndex& source_parent) const;
    virtual bool filterAcceptsColumn(int source_column, const QModelIndex& source_parent) const;

private:
    SubsetProxyModelPrivate* const d_ptr;
    Q_DECLARE_PRIVATE(SubsetProxyModel)
};

#endif // SUBSETPROXYMODEL_H