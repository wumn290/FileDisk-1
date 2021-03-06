/*
    This is a virtual disk driver for Windows that uses one or more files to
    emulate physical disks.
    Copyright (C) 1999-2009 Bo Brant閚.
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _FILE_DISK_
#define _FILE_DISK_

#define FILE_DISK_POOL_TAG 'ksiD'

#ifndef __T
#ifdef _NTDDK_
#define __T(x)  L ## x
#else
#define __T(x)  x
#endif
#endif

#ifndef _T
#define _T(x)   __T(x)
#endif

#define DEVICE_BASE_NAME    _T("\\FileDisk")
#define DEVICE_DIR_NAME     _T("\\Device")      DEVICE_BASE_NAME
#define DEVICE_NAME_PREFIX  DEVICE_DIR_NAME     DEVICE_BASE_NAME

#define IOCTL_FILE_DISK_OPEN_FILE   CTL_CODE(FILE_DEVICE_DISK, 0x800, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_CLOSE_FILE  CTL_CODE(FILE_DEVICE_DISK, 0x801, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)
#define IOCTL_FILE_DISK_QUERY_FILE  CTL_CODE(FILE_DEVICE_DISK, 0x802, METHOD_BUFFERED, FILE_READ_ACCESS)
#define IOCTL_FILE_DISK_QUERY_DEVICE_STATUS  CTL_CODE(FILE_DEVICE_DISK, 0x803, METHOD_BUFFERED, FILE_READ_ACCESS | FILE_WRITE_ACCESS)     //获取设备是否可用

typedef struct _OPEN_FILE_INFORMATION {
    LARGE_INTEGER   FileSize;
	LARGE_INTEGER	FileOffset;			//记录文件系统偏移
    BOOLEAN         ReadOnly;
	BOOLEAN			PhysicalDrive;		//判断是否为物理磁盘
    UCHAR           DriveLetter;
    USHORT          FileNameLength;
    CHAR            FileName[1];
} OPEN_FILE_INFORMATION, *POPEN_FILE_INFORMATION;

typedef enum _NPMINI_COMMAND {
	ENUM_AUTHORITY = 0,
	ENUM_EXCEPTPROCESSID,
	ENUM_FORMATTING,
	ENUM_BACKFILEPATH,
	ENUM_BACKFILEEXTENTION				//文件扩展名
} NPMINI_COMMAND;

typedef struct _COMMAND_MESSAGE {
	NPMINI_COMMAND 	Command;				//信息类别
	ULONG			commandContext;			//信息内容
	WCHAR			backFilePath[256];		//文件审计存储路径
} COMMAND_MESSAGE, *PCOMMAND_MESSAGE;

#endif
