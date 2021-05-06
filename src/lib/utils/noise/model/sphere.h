// sphere.h
//
// Copyright (C) 2003, 2004 Jason Bevins
//
// This library is free software; you can redistribute it and/or modify it
// under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation; either version 2.1 of the License, or (at
// your option) any later version.
//
// This library is distributed in the hope that it will be useful, but WITHOUT
// ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
// FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
// License (COPYING.txt) for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with this library; if not, write to the Free Software Foundation,
// Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
// The developer's email is jlbezigvins@gmzigail.com (for great email, take
// off every 'zig'.)
//

#ifndef NOISE_MODEL_SPHERE_H
#define NOISE_MODEL_SPHERE_H

#include <cassert>
#include "../module/modulebase.h"

namespace noise {

	namespace model {

		/// @addtogroup libnoise
		/// @{

		/// @addtogroup models
		/// @{

		/// Model that defines the surface of a sphere.
		///
		/// @image html modelsphere.png
		///
		/// This model returns an output value from a noise module given the
		/// coordinates of an input value located on the surface of a sphere.
		///
		/// To build an output value, pass the (latitude, longitude)
		/// coordinates of an input value to the GetValue() method.
		///
		/// This model is useful for creating:
		/// - seamless textures that can be mapped onto a sphere
		/// - terrain height maps for entire planets
		///
		/// This sphere has a radius of 1.0 unit and its center is located at
		/// the origin.
		class Sphere {

		public:

			/// Constructor.
			Sphere();

			/// Constructor
			///
			/// @param module The noise module that is used to build the output
			/// values.
			Sphere(const module::Module& module);

			/// Returns the noise module that is used to build the output
			/// values.
			///
			/// @returns A reference to the noise module.
			///
			/// @pre A noise module was passed to the SetModule() method.
			const module::Module& GetModule() const {
				assert (m_pModule != NULL);
				return *m_pModule;
			}

			/// Returns the output value from the noise module given the
			/// (latitude, longitude) coordinates of the specified input value
			/// located on the surface of the sphere.
			///
			/// @param lat The latitude of the input value, in degrees.
			/// @param lon The longitude of the input value, in degrees.
			///
			/// @returns The output value from the noise module.
			///
			/// @pre A noise module was passed to the SetModule() method.
			///
			/// This output value is generated by the noise module passed to the
			/// SetModule() method.
			///
			/// Use a negative latitude if the input value is located on the
			/// southern hemisphere.
			///
			/// Use a negative longitude if the input value is located on the
			/// western hemisphere.
			double GetValue(double lat, double lon) const;

			/// Sets the noise module that is used to build the output values.
			///
			/// @param module The noise module that is used to build the output
			/// values.
			///
			/// This noise module must exist for the lifetime of this object,
			/// until you pass a new noise module to this method.
			void SetModule(const module::Module& module) {
				m_pModule = &module;
			}

		private:

			/// A pointer to the noise module used to build the output values.
			const module::Module* m_pModule;

		};

		/// @}

		/// @}

	}

}

#endif
