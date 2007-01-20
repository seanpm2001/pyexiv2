// *****************************************************************************
/*
 * Copyright (C) 2006 Olivier Tilloy <olivier@tilloy.net>
 *
 * This file is part of the pyexiv2 distribution.
 *
 * pyexiv2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * pyexiv2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with pyexiv2; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, 5th Floor, Boston, MA 02110-1301 USA.
 */
/*
  File:      libpyexiv2.hpp
  Author(s): Olivier Tilloy <olivier@tilloy.net>
 */
// *****************************************************************************

#ifndef __libpyexiv2_wrapper__
#define __libpyexiv2_wrapper__

#include <string>

#include "exiv2/image.hpp"
#include "exiv2/exif.hpp"
#include "exiv2/iptc.hpp"

#include <boost/python.hpp>

namespace LibPyExiv2
{

	class Image
	{
	public:
		// Constructors
		Image(std::string filename);
		Image(const Image & image);

		void readMetadata();
		void writeMetadata();

		// Read and write access to the EXIF tags.
		// For a complete list of the available EXIF tags, see
		// libexiv2's documentation (http://exiv2.org/tags.html).

		// Returns a list of all the keys of available EXIF tags set in the
		// image.
		boost::python::list getAvailableExifTags();

		// Returns a tuple containing the type (as a string) and the value
		// (as a string as well) of the required EXIF tag, empty strings if
		// the tag does not exist.
		boost::python::tuple getExifTag(std::string key);

		// Returns a human-readable string containing the value of the
		// required EXIF tag, empty if the tag does not exist.
		std::string getExifTagToString(std::string key);

		// Sets the EXIF tag's value and returns a tuple containing the
		// type and previous value of the tag. If the tag was not set
		// before, it is created.
		boost::python::tuple setExifTag(std::string key, std::string value);

		// Deletes the required EXIF tag and returns a tuple containing the
		// type and previous value if it existed, empty strings otherwise.
		boost::python::tuple deleteExifTag(std::string key);

		// Read and write access to the IPTC tags.
		// For a complete list of the available IPTC tags, see
		// libexiv2's documentation (http://exiv2.org/iptc.html).

		// Returns a list of all the keys of available IPTC tags set in the
		// image.
		boost::python::list getAvailableIptcTags();

		// Returns a tuple containing the type (as a string) and the value
		// (as a string as well) of the required IPTC tag, empty strings if
		// the tag does not exist.
		boost::python::tuple getIptcTag(std::string key);

		// Sets the IPTC tag's value and returns a tuple containing the
		// type and previous value of the tag. If the tag was not set
		// before, it is created.
		boost::python::tuple setIptcTag(std::string key, std::string value);

		// Deletes the required IPTC tag and returns a tuple containing the
		// type and previous value if it existed, empty strings otherwise.
		boost::python::tuple deleteIptcTag(std::string key);

		// Read and write access to the thumbnail embedded in the image.

		// Returns a tuple containing the format of the thumbnail ("TIFF" or
		// "JPEG") and the thumbnail raw data as a string buffer.
		boost::python::tuple getThumbnailData();

		// Sets the thumbnail of the image. The parameter is the thumbnail raw
		// jpeg data as a string buffer.
		void setThumbnailData(std::string data);

		// Deletes the thumbnail embedded in the image.
		void deleteThumbnail();

		// Writes the thumbnail to an image file.
		// A filename extension is appended to the given path according to the
		// image type of the thumbnail, so it should not include an extension.
		void dumpThumbnailToFile(const std::string path);

		// Sets the image contained in the jpeg file passed as a parameter as
		// the thumbnail of the image.
		void setThumbnailFromJpegFile(const std::string path);

	private:
		std::string _filename;
		Exiv2::Image::AutoPtr _image;
		Exiv2::ExifData _exifData;
		Exiv2::IptcData _iptcData;

		// true if the image's internal metadata has already been read,
		// false otherwise
		bool _dataRead;
	};

	// Translate an Exiv2 generic exception into a Python exception
	void translateExiv2Error(Exiv2::Error const& e);

} // End of namespace LibPyExiv2

#endif
