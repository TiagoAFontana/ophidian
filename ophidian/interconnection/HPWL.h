/*
 * Copyright 2016 Ophidian
   Licensed to the Apache Software Foundation (ASF) under one
   or more contributor license agreements.  See the NOTICE file
   distributed with this work for additional information
   regarding copyright ownership.  The ASF licenses this file
   to you under the Apache License, Version 2.0 (the
   "License"); you may not use this file except in compliance
   with the License.  You may obtain a copy of the License at

   http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing,
   software distributed under the License is distributed on an
   "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
   KIND, either express or implied.  See the License for the
   specific language governing permissions and limitations
   under the License.
 */


#ifndef OPHIDIAN_INTERCONNECTION_HPWL_H
#define OPHIDIAN_INTERCONNECTION_HPWL_H

#include <ophidian/util/Units.h>
#include <ophidian/util/Range.h>

namespace ophidian
{
/// The Interonnection namespace
namespace interconnection
{
/// HPWL calculation
/**
 *   Calculates the half-perimeter of the minimum bounding box that covers a set of points.
 *   \param points A vector of points.
 **/
double hpwl(const std::vector< ophidian::util::LocationDbu > & points);
double hpwl(std::vector<util::LocationDbu>::const_iterator begin, std::vector<util::LocationDbu>::const_iterator end);
} // namespace interconnection
} // namespace ophidian


#endif //OPHIDIAN_INTERCONNECTION_HPWL_H
