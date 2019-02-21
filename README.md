This is a collection of proxy models for Qt 5.
They are used to manipulate a source model either for display in a widget or for further processing.
Qt model proxies are typically fairly tedious to write because of the large number of events they must handle (moving and removal of columns and rows, etc.).
Although it's always *possible* to write a proxy model that performs precisely the transformation you want, this is error-prone, and it's usually also possible to implement this transformation in terms of a few basic operations, such as transposition and sort.

The library is licensed under the [wxWidgets license](https://www.wxwidgets.org/about/licence/), which means that it is licensed under the LGPL, but with a linking exception that allows proprietary software to easily use the library with few restrictions.

These classes aim to alleviate the pain of writing custom proxies where a chain of one or more proxies would suffice.
They are designed to be chained together with each other and with other proxies, either those provided by the user or built-in Qt proxies.
Below is a list of the provided classes with a brief description of each.

## Class Description

All these proxies inherit from `QAbstractProxyModel`, so their source models can all be set via the standard method:

    QAbstractProxyModel::setSourceModel(QAbstractItemModel*)

### TranspositionProxyModel

This class applies a matrix transpose operation on its source model.
That is, given the source model:

    A1  A2
    B1  B2
    C1  C2

it presents to its consumers the transposition:

    A1  B1  C1
    A2  B2  C2

This class exposes no settings.

Despite its simplicity, this class is surprisingly handy!
One nice use case is to use it together with a suitable filter (such as KDE's `KSelectionProxyModel`) to display a selected row from one table as a vertical list in a second widget.

### SubsetProxyModel

This class is a simple filter that exposes a "slice" of its source model.
This class presents a smaller subset inclusively defined by two QModelIndexes, the top left and bottom right corners of the subset.
As an example, given the source model:

    A1  A2
    B1  B2
    C1  C2

and the bounds (in the format `(row, column)`) `(0, 0)` and `(2, 0)`, the proxied model looks like this:

    A1
    B1
    C1

Again, note that the bounds are inclusive and zero-based, as is usual with QModelIndex.
The bounds can both be set at once via

    SubsetProxyModel::setBounds(QModelIndex, QModelIndex)

or individually via the members:

    SubsetProxyModel::setTopLeftBound(QModelIndex)
    SubsetProxyModel::setBottomRightBound(QModelIndex)

