/*
 *      Copyright (C) 2005-2013 Team XBMC
 *      http://www.xbmc.org
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

#include "DirectoryNodeOverview.h"
#include "FileItem.h"
#include "pictures/PictureDatabase.h"
#include "guilib/LocalizeStrings.h"

namespace XFILE
{
    namespace PICTUREDATABASEDIRECTORY
    {
        Node OverviewChildren[] = {
            { NODE_TYPE_LOCATION,                 "location",               135 },
            { NODE_TYPE_FACE,                "face",              133 },
            { NODE_TYPE_PICTUREALBUM,                 "picturealbums",               132 },
            { NODE_TYPE_SINGLES,               "singles",              1050 },
            { NODE_TYPE_PICTURE,                  "picture",                134 },
            { NODE_TYPE_YEAR,                  "years",                652 },
            { NODE_TYPE_TOP100,                "top100",               271 },
            { NODE_TYPE_PICTUREALBUM_RECENTLY_ADDED,  "recentlyaddedalbums",  359 },
            { NODE_TYPE_PICTUREALBUM_RECENTLY_PLAYED, "recentlyplayedalbums", 517 },
            { NODE_TYPE_PICTUREALBUM_COMPILATIONS,    "compilations",         521 },
        };
    };
};

using namespace std;
using namespace XFILE::PICTUREDATABASEDIRECTORY;

CDirectoryNodeOverview::CDirectoryNodeOverview(const CStdString& strName, CDirectoryNode* pParent)
: CDirectoryNode(NODE_TYPE_OVERVIEW, strName, pParent)
{
    
}

NODE_TYPE CDirectoryNodeOverview::GetChildType() const
{
    for (unsigned int i = 0; i < sizeof(OverviewChildren) / sizeof(Node); ++i)
        if (GetName().Equals(OverviewChildren[i].id.c_str()))
            return OverviewChildren[i].node;
    return NODE_TYPE_NONE;
}

CStdString CDirectoryNodeOverview::GetLocalizedName() const
{
    for (unsigned int i = 0; i < sizeof(OverviewChildren) / sizeof(Node); ++i)
        if (GetName().Equals(OverviewChildren[i].id.c_str()))
            return g_localizeStrings.Get(OverviewChildren[i].label);
    return "";
}

bool CDirectoryNodeOverview::GetContent(CFileItemList& items) const
{
    CMusicDatabase musicDatabase;
    bool showSingles = false;
    if (musicDatabase.Open())
    {
        CDatabase::Filter filter("songview.idAlbum IN (SELECT idAlbum FROM album WHERE strAlbum = '')");
        if (musicDatabase.GetSongsCount(filter) > 0)
            showSingles = true;
    }
    
    for (unsigned int i = 0; i < sizeof(OverviewChildren) / sizeof(Node); ++i)
    {
        if (i == 3 && !showSingles) // singles
            continue;
        if (i == 9 && musicDatabase.GetCompilationAlbumsCount() == 0) // compilations
            continue;
        
        CFileItemPtr pItem(new CFileItem(g_localizeStrings.Get(OverviewChildren[i].label)));
        CStdString strDir;
        strDir.Format("%s/", OverviewChildren[i].id);
        pItem->SetPath(BuildPath() + strDir);
        pItem->m_bIsFolder = true;
        pItem->SetCanQueue(false);
        items.Add(pItem);
    }
    
    return true;
}
