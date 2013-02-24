/*
Frhed - Free hex editor
Copyright (C) 2000 Raihan Kibria

This program is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License, version 2, as published by
the Free Software Foundation.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with this program; see the file COPYING.  If not, write to the Free
Software Foundation, 59 Temple Place - Suite 330, Boston, MA
02111-1307, USA.

Last change: 2013-02-24 by Jochen Neubeck
*/
#include "precomp.h"
#include "physicaldrive.h"
#include "PDriveNT.h"

BOOL PNtPhysicalDrive::GetDriveLayout(LPBYTE lpbMemory, DWORD dwSize)
{
	DWORD junk;

	return DeviceIoControl(m_hDevice, // the device we are querying
		IOCTL_DISK_GET_DRIVE_LAYOUT, // operation to perform
		NULL, 0, // no input buffer, so we pass zero
		lpbMemory, dwSize, // the output buffer
		&junk, // discard the count of bytes returned
		NULL);
} // GetDriveLayout()

BOOL PNtPhysicalDrive::GetDriveLayoutEx(LPBYTE lpbMemory, DWORD dwSize)
{
	DWORD junk;

	return DeviceIoControl(m_hDevice, // the device we are querying
		IOCTL_DISK_GET_DRIVE_LAYOUT_EX, // operation to perform
		NULL, 0, // no input buffer, so we pass zero
		lpbMemory, dwSize, // the output buffer
		&junk, // discard the count of bytes returned
		NULL);
} // GetDriveLayout()

BOOL PNtPhysicalDrive::GetDriveGeometry(DISK_GEOMETRY* lpDG)
{
	DWORD junk;

	return DeviceIoControl(m_hDevice, // the device we are querying
		IOCTL_DISK_GET_DRIVE_GEOMETRY, // operation to perform
		NULL, 0, // no input buffer, so we pass zero
		lpDG, sizeof(DISK_GEOMETRY), // the output buffer
		&junk, // discard the count of bytes returned
		NULL);
} // GetDriveGeometry()

BOOL PNtPhysicalDrive::GetDriveGeometryEx(DISK_GEOMETRY_EX* lpDG, DWORD dwSize)
{
	DWORD junk;

	return DeviceIoControl(m_hDevice, // the device we are querying
		IOCTL_DISK_GET_DRIVE_GEOMETRY_EX, // operation to perform
		NULL, 0, // no input buffer, so we pass zero
		lpDG, dwSize, // the output buffer
		&junk, // discard the count of bytes returned
		NULL);
} // GetDriveGeometry()

BOOL PNtPhysicalDrive::Open(int iDrive)
{
	Close();

	TCHAR szPath[256];
	_stprintf(szPath, _T("\\\\.\\PhysicalDrive%d"), iDrive);

	m_hDevice = CreateFile(szPath, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		DISK_GEOMETRY dg;
		if (GetDriveGeometry(&dg))
		{
			m_BytesPerSector = dg.BytesPerSector;
			return TRUE;
		}
	}
	return FALSE;
}

void PNtPhysicalDrive::Close()
{
	if (m_hDevice != INVALID_HANDLE_VALUE)
	{
		CloseHandle(m_hDevice);
		m_hDevice = INVALID_HANDLE_VALUE;
	}
}

BOOL PNtPhysicalDrive::ReadAbsolute(LPBYTE lpbMemory, DWORD dwSize, INT64 Sector)
{
	LARGE_INTEGER li;
	li.QuadPart = Sector;
	li.QuadPart *= m_BytesPerSector;
	SetFilePointer(m_hDevice, li.LowPart, &li.HighPart, FILE_BEGIN);
	return ReadFile(m_hDevice, lpbMemory, dwSize, &li.LowPart, 0);
} // ReadAbsolute()

PNtPhysicalDrive::PNtPhysicalDrive()
{
	m_hDevice = INVALID_HANDLE_VALUE;
} // PNtPhysicalDrive()

PNtPhysicalDrive::~PNtPhysicalDrive()
{
	Close();
} // ~PNtPhysicalDrive()

BOOL PNtPhysicalDrive::IsOpen()
{
	return (m_hDevice != INVALID_HANDLE_VALUE);
}

