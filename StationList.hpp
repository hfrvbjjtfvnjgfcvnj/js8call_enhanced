#ifndef STATION_LIST_HPP__
#define STATION_LIST_HPP__

#include <QSortFilterProxyModel>
#include <QDateTime>
#include <QString>
#include <QList>

#include "pimpl_h.hpp"

#include "Radio.hpp"

class Bands;

//
// Class StationList
//
//  Encapsulates information  about a  collection of  unique operating
//  stations per  band. The implementation  is a table model  with the
//  first column  being the unique  (within the table rows)  band name
//  and, the  second the frequency  offset for transverter  usage and,
//  the third the antenna description. All are editable.
//
// Responsibilities
//
//  Stores internally an unordered table of bands.
//
//  If  an ordered  representaion is  required then  wrapping with  an
//  appropriate        proxy         model        is        sufficient
//  e.g. QSortFilterProxyModel. A custom SortRole role is provided for
//  the band  name column which  returns a numeric value  (Bands lower
//  frequency limit) which gives a strict frequency ordering by band.
//
// Collaborations
//
//  Implements the  QAbstractTableModel interface for a  grid of bands
//  with offset frequencies and antenna descriptions.
//
//  Uses the Bands model to lookup band information.
//
class StationList final
  : public QSortFilterProxyModel
{
public:
  using Frequency = Radio::Frequency;
  using FrequencyDelta = Radio::FrequencyDelta;

  //
  // Struct Station
  //
  //  Aggregation of fields that describe a radio station on a band.
  //
  struct Station
  {
    QString band_name_;
    Frequency frequency_;
    QDateTime switch_at_;
    QDateTime switch_until_;
    QString day_of_week_;
    bool enable_autotx_;
    QString description_;
  };

  using Stations = QList<Station>;

  enum Column {band_column, frequency_column, switch_at_column, switch_until_column, day_of_week_column, enable_autotx_column, description_column};

  explicit StationList (Bands const * bands, QObject * parent = nullptr);
  explicit StationList (Bands const * bands, Stations, QObject * parent = nullptr);
  ~StationList ();

  // Load and query contents.
  Stations station_list (Stations);
  Stations const& station_list () const;

  //
  // Model API
  //
  QModelIndex add (Station);                 // Add a new Station
  bool remove (Station);                     // Remove a Station
  bool removeDisjointRows (QModelIndexList); // Remove one or more stations

  // Custom sort role.
  static int constexpr SortRole = Qt::UserRole;

private:
  class impl;
  pimpl<impl> m_;
};

// Station equivalence
inline
bool operator == (StationList::Station const& lhs, StationList::Station const& rhs)
{
  return lhs.band_name_ == rhs.band_name_ &&
    lhs.description_ == rhs.description_ &&
    lhs.frequency_ == rhs.frequency_ &&
    lhs.switch_at_ == rhs.switch_at_ &&
    lhs.switch_until_ == rhs.switch_until_ &&
    lhs.day_of_week_ == rhs.day_of_week_ && 
    lhs.enable_autotx_ == rhs.enable_autotx_;
}

QDataStream& operator << (QDataStream&, StationList::Station const&);
QDataStream& operator >> (QDataStream&, StationList::Station&);

#if !defined (QT_NO_DEBUG_STREAM)
QDebug operator << (QDebug debug, StationList::Station const&);
#endif

Q_DECLARE_METATYPE (StationList::Station);
Q_DECLARE_METATYPE (StationList::Stations);

#endif
