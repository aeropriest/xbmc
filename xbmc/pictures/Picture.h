#pragma once
/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 */
/*!
 \file Picture.h
 \brief
 */
#pragma once

#include "utils/StdString.h"
#include "utils/ISerializable.h"
#include "XBDateTime.h"
#include "pictures/tags/PictureInfoTag.h" // for EmbeddedArt
#include "Face.h"
#include <map>
#include <vector>

#include "utils/StdString.h"
#include "utils/Job.h"

class CBaseTexture;

/*!
 \ingroup music
 \brief Class to store and read album information from CPictureDatabase
 \sa CPicture, CPictureDatabase
 */

class CLocation
{
public:
    long idLocation;
    CStdString strLocation;
};

class CFileItem;

/*!
 \ingroup music
 \brief Class to store and read song information from CPictureDatabase
 \sa CAlbum, CPictureDatabase
 */
class CPicture: public ISerializable
{
public:
    CPicture() ;
    CPicture(CFileItem& item);
    virtual ~CPicture(){};
    void Clear() ;
    virtual void Serialize(CVariant& value) const;
    
    bool operator<(const CPicture &song) const
    {
        if (strFileName < song.strFileName) return true;
        if (strFileName > song.strFileName) return false;
        return false;
    }
    
    /*! \brief whether this song has art associated with it
     Tests both the strThumb and embeddedArt members.
     */
    bool HasArt() const;
    
    /*! \brief whether the art from this song matches the art from another
     Tests both the strThumb and embeddedArt members.
     */
    bool ArtMatches(const CPicture &right) const;
    
    
    static bool CreateThumbnailFromSurface(const unsigned char* buffer, int width, int height, int stride, const CStdString &thumbFile);
    
    /*! \brief Create a tiled thumb of the given files
     \param files the files to create the thumb from
     \param thumb the filename of the thumb
     */
    static bool CreateTiledThumb(const std::vector<std::string> &files, const std::string &thumb);
    
    /*! \brief Cache a texture, resizing, rotating and flipping as needed, and saving as a JPG or PNG
     \param texture a pointer to a CBaseTexture
     \param dest_width [in/out] maximum width in pixels of cached version - replaced with actual cached width
     \param dest_height [in/out] maximum height in pixels of cached version - replaced with actual cached height
     \param dest the output cache file
     \return true if successful, false otherwise
     */
    static bool CacheTexture(CBaseTexture *texture, uint32_t &dest_width, uint32_t &dest_height, const std::string &dest);
    static bool CacheTexture(uint8_t *pixels, uint32_t width, uint32_t height, uint32_t pitch, int orientation, uint32_t &dest_width, uint32_t &dest_height, const std::string &dest);
    
private:
    static void GetScale(unsigned int width, unsigned int height, unsigned int &out_width, unsigned int &out_height);
    static bool ScaleImage(uint8_t *in_pixels, unsigned int in_width, unsigned int in_height, unsigned int in_pitch,
                           uint8_t *out_pixels, unsigned int out_width, unsigned int out_height, unsigned int out_pitch);
    static bool OrientateImage(uint32_t *&pixels, unsigned int &width, unsigned int &height, int orientation);
    
    static bool FlipHorizontal(uint32_t *&pixels, unsigned int &width, unsigned int &height);
    static bool FlipVertical(uint32_t *&pixels, unsigned int &width, unsigned int &height);
    static bool Rotate90CCW(uint32_t *&pixels, unsigned int &width, unsigned int &height);
    static bool Rotate270CCW(uint32_t *&pixels, unsigned int &width, unsigned int &height);
    static bool Rotate180CCW(uint32_t *&pixels, unsigned int &width, unsigned int &height);
    static bool Transpose(uint32_t *&pixels, unsigned int &width, unsigned int &height);
    static bool TransposeOffAxis(uint32_t *&pixels, unsigned int &width, unsigned int &height);
public:
    long idPicture;
    int idAlbum;
    CStdString strFileName;
    CStdString strTitle;
    CStdString strPictureType;
    CStdString strOrientation;
    std::vector<std::string> face;
    VECFACECREDITS faceCredits;
    CStdString strAlbum;
    std::vector<std::string> albumFace;
    std::vector<std::string> location;
    CStdString strThumb;
    PICTURE_INFO::EmbeddedArtInfo embeddedArt;
    CStdString strComment;
    CDateTime takenOn;
};


//this class calls CreateThumbnailFromSurface in a CJob, so a png file can be written without halting the render thread
class CThumbnailWriter : public CJob
{
  public:
    //WARNING: buffer is deleted from DoWork()
    CThumbnailWriter(unsigned char* buffer, int width, int height, int stride, const CStdString& thumbFile);
    bool DoWork();

  private:
    unsigned char* m_buffer;
    int            m_width;
    int            m_height;
    int            m_stride;
    CStdString     m_thumbFile;
};


/*!
 \ingroup music
 \brief A map of CPicture objects, used for CPictureDatabase
 */
typedef std::map<std::string, CPicture> MAPPICTURES;

/*!
 \ingroup music
 \brief A vector of CPicture objects, used for CPictureDatabase
 \sa CPictureDatabase
 */
typedef std::vector<CPicture> VECPICTURES;

/*!
 \ingroup music
 \brief A vector of CStdString objects, used for CPictureDatabase
 \sa CPictureDatabase
 */
typedef std::vector<CLocation> VECLOCATIONS;




