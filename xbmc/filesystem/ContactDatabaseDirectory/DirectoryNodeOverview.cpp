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
#include "contacts/ContactDatabase.h"
#include "guilib/LocalizeStrings.h"

namespace XFILE
{
  namespace CONTACTDATABASEDIRECTORY
  {
    Node OverviewChildren[] = {
      { NODE_TYPE_LOCATION,                 "locations",               135 },
      { NODE_TYPE_FACE,                "faces",              133 },
      { NODE_TYPE_CONTACT,                  "contacts",                134 },
      { NODE_TYPE_CONTACT_RECENTLY_ADDED,  "recentlyaddedcontacts",  359 },
    };
  };
};

using namespace std;
using namespace XFILE::CONTACTDATABASEDIRECTORY;

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
  CContactDatabase contactDatabase;
  bool showSingles = false;
  if (contactDatabase.Open())
  {
    CDatabase::Filter filter("songview.idAlbum IN (SELECT idAlbum FROM album WHERE strAlbum = '')");
    if (contactDatabase.GetContactsCount(filter) > 0)
      showSingles = true;
  }
  
  for (unsigned int i = 0; i < sizeof(OverviewChildren) / sizeof(Node); ++i)
  {
    if (i == 3 && !showSingles) // singles
      continue;
//    if (i == 9 && contactDatabase.GetCompilationAlbumsCount() == 0) // compilations
//      continue;
    
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
