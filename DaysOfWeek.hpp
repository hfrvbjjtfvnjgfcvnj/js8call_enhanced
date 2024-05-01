#ifndef DAYSOFWEEK_HPP__
#define DAYSOFWEEK_HPP__

#include <QAbstractListModel>

#include "qt_helpers.hpp"

class QString;
class QVariant;
class QModelIndex;

//
// Class DaysOfWeek - Qt model that implements the list of Days of the Week
//
//
// Responsibilities
//
// 	Provides  a  single column  list  model  that contains  the  human
// 	readable  string  version  of  options for days of the week  in  the  display
// 	role. Also  provided is  a translatable  column header  string and
// 	tool tip string.
//
//
// Collaborations
//
// 	Implements a concrete sub-class of the QAbstractListModel class.
//
class DaysOfWeek final
  : public QAbstractListModel
{
  Q_OBJECT
  Q_ENUMS (DoW)

public:
  //
  // This enumeration  contains the  supported Days of the Week
  // (DaysOfWeek.cpp) must be maintained in parallel.
  //
  enum DoW
  {
    Daily,                        // matches with all days of the week
    Sunday,
    Monday,
    Tuesday,
    Wednesday,
    Thursday,
    Friday,
    Saturday,
    SENTINAL                    // this must be last
  };
  Q_ENUM (DoW)

  explicit DaysOfWeek (QObject * parent = nullptr);

  // translate between enumeration and human readable strings
  static char const * name (DoW);
  static DoW value (QString const&);

  // Implement the QAbstractListModel interface
  int rowCount (QModelIndex const& parent = QModelIndex {}) const override
  {
    return parent.isValid () ? 0 : SENTINAL; // Number of values in DoW enumeration class
  }
  QVariant data (QModelIndex const&, int role = Qt::DisplayRole) const override;
  QVariant headerData (int section, Qt::Orientation, int = Qt::DisplayRole) const override;
};

// Qt boilerplate  to make the IARURegions::region  enumeration a type
// that can  be streamed and  queued as a  signal argument as  well as
// showing the human readable string when output to debug streams.
#if QT_VERSION < 0x050500
// Qt 5.5 introduces the Q_ENUM macro which automatically registers
// the meta-type
Q_DECLARE_METATYPE (DaysOfWeek::DoW);
#endif

#if !defined (QT_NO_DEBUG_STREAM)
ENUM_QDEBUG_OPS_DECL (DaysOfWeek, DoW);
#endif

ENUM_QDATASTREAM_OPS_DECL (DaysOfWeek, DoW);
ENUM_CONVERSION_OPS_DECL (DaysOfWeek, DoW);

#endif
