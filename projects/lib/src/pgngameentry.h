/*
    This file is part of Cute Chess.

    Cute Chess is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Cute Chess is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Cute Chess.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef PGNGAMEENTRY_H
#define PGNGAMEENTRY_H

#include <QDate>
#include "board/result.h"
class PgnStream;
class QDataStream;


/*!
 * \brief An entry in a PGN collection.
 *
 * A PgnGameEntry object contains the tags of a PGN game, and
 * the position and line number in a PGN stream.
 * This class was designed for high-performance and low memory
 * consumption, which is useful for quickly loading large game
 * collections.
 *
 * \sa PgnGame, PgnStream
 */
class LIB_EXPORT PgnGameEntry
{
	public:
		/*! Creates a new empty PgnGameEntry object. */
		explicit PgnGameEntry();

		/*! Resets the entry to an empty default. */
		void clear();
		/*!
		 * Reads an entry from a PGN stream.
		 * Returns true if successfull.
		 */
		bool read(PgnStream& in);

		/*!
		 * Reads an entry from data stream.
		 * Returns true if successfull.
		 */
		bool read(QDataStream& in);

		/*!
		 * Writes an entry to data stream.
		 */
		void write(QDataStream& out) const;

		/*!
		 * Returns true if the PGN tags match the wildcard \a pattern.
		 * The matching is case insensitive.
		 */
		bool match(const QByteArray& pattern) const;

		/*! Returns the stream position where the game begins. */
		qint64 pos() const;
		/*! Returns the line number where the game begins. */
		qint64 lineNumber() const;

		/*! Returns the event/tournament name. */
		QString event() const;
		/*! Returns the site/location where the game was played. */
		QString site() const;
		/*! Returns the starting date of the game. */
		QDate date() const;
		/*! Returns the round number of a match or tournament. */
		int round() const;
		/*! Returns the name of the white player. */
		QString white() const;
		/*! Returns the name of the black player. */
		QString black() const;
		/*! Returns the game's chess variant. */
		QString variant() const;
		/*! Returns the game result. */
		Chess::Result result() const;

	private:
		enum TagType
		{
			EventTag,
			SiteTag,
			DateTag,
			RoundTag,
			WhiteTag,
			BlackTag,
			ResultTag,
			VariantTag
		};

		QString tagValue(TagType type) const;
		void addTag(const QByteArray& tagValue);

		QByteArray m_data;

		qint64 m_pos;
		qint64 m_lineNumber;
};

/*! Reads a PGN game entry from a PGN stream. */
extern LIB_EXPORT PgnStream& operator>>(PgnStream& in, PgnGameEntry& entry);

/*! Reads a PGN game entry from a data stream. */
extern LIB_EXPORT QDataStream& operator>>(QDataStream& in, PgnGameEntry& entry);

/*! Writes a PGN game entry to a data stream. */
extern LIB_EXPORT QDataStream& operator<<(QDataStream& out,
                                          const PgnGameEntry& entry);

#endif // PGNGAMEENTRY_H
