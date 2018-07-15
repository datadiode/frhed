/* Copyright 2013 David Axmark

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

	http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

This is an edited version of code obtained from:
https://github.com/MoSync/MoSync/blob/master/libs/MAUtil

Last change: 2018-06-13 by Jochen Neubeck
*/

#include "precomp.h"
#include "RefCounted.h"

namespace MAUtil {

	RefCounted::RefCounted(int startCount) : mRefCount(startCount) {}

	void RefCounted::addRef() {
		mRefCount++;
	}

	void RefCounted::release() {
		mRefCount--;
		if(mRefCount == 0) {
			delete this;
		}
	}

	int RefCounted::getRefCount() {
		return mRefCount;
	}
}
