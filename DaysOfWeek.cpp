#include "DaysOfWeek.hpp"

#include <algorithm>

#include <QString>
#include <QVariant>
#include <QModelIndex>
#include <QMetaType>

#include "moc_DaysOfWeek.cpp"

namespace
{
  // human readable strings for each Day of Week enumeration value
  char const * const dow_names[] =
  {
    "Daily",
    "Sunday",
    "Monday",
    "Tuesday",
    "Wednesday",
    "Thursday", 
    "Friday",
    "Saturday",
  };
  std::size_t constexpr dow_names_size = sizeof (dow_names) / sizeof (dow_names[0]);
}

DaysOfWeek::DaysOfWeek (QObject * parent)
  : QAbstractListModel {parent}
{
  static_assert (dow_names_size == SENTINAL,
                 "dow_names array must match DaysOfWeek enumeration");
}

char const * DaysOfWeek::name (DoW r)
{
  return dow_names[static_cast<int> (r)];
}

auto DaysOfWeek::value (QString const& s) -> DoW
{
  auto end = dow_names + dow_names_size;
  auto p = std::find_if (dow_names, end
                         , [&s] (char const * const name) {
                           return name == s;
                         });
  return p != end ? static_cast<DoW> (p - dow_names) : Daily;
}

QVariant DaysOfWeek::data (QModelIndex const& index, int role) const
{
  QVariant item;

  if (index.isValid ())
    {
      auto const& row = index.row ();
      switch (role)
        {
        case Qt::ToolTipRole:
        case Qt::AccessibleDescriptionRole:
          item = tr ("Day of the Week (Local Time)");
          break;

        case Qt::EditRole:
          item = static_cast<DoW> (row);
          break;

        case Qt::DisplayRole:
        case Qt::AccessibleTextRole:
          item = dow_names[row];
          break;

        case Qt::TextAlignmentRole:
          item = Qt::AlignHCenter + Qt::AlignVCenter;
          break;
        }
    }

  return item;
}

QVariant DaysOfWeek::headerData (int section, Qt::Orientation orientation, int role) const
{
  QVariant result;

  if (Qt::DisplayRole == role && Qt::Horizontal == orientation)
    {
      result = tr ("Day of the Week (Local Time)");
    }
  else
    {
      result = QAbstractListModel::headerData (section, orientation, role);
    }

  return result;
}

#if !defined (QT_NO_DEBUG_STREAM)
ENUM_QDEBUG_OPS_IMPL (DaysOfWeek, DoW);
#endif

ENUM_QDATASTREAM_OPS_IMPL (DaysOfWeek, DoW);
ENUM_CONVERSION_OPS_IMPL (DaysOfWeek, DoW);
