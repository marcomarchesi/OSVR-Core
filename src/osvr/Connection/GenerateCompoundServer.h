/** @file
    @brief Header

    @date 2015

    @author
    Sensics, Inc.
    <http://sensics.com/osvr>
*/

// Copyright 2015 Sensics, Inc.
//
// All rights reserved.
//
// (Final version intended to be licensed under
// the Apache License, Version 2.0)

#ifndef INCLUDED_GenerateCompoundServer_h_GUID_55F870FA_C398_49B8_9907_A007B3C6F8CA
#define INCLUDED_GenerateCompoundServer_h_GUID_55F870FA_C398_49B8_9907_A007B3C6F8CA

// Internal Includes
#include <osvr/Util/UniquePtr.h>

// Library/third-party includes
#include <boost/mpl/begin_end.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/next.hpp>
#include <boost/type_traits/is_same.hpp>

// Standard includes
// - none

namespace osvr {
namespace connection {

    /// @brief Metaprogramming to generate a VRPN server object out of an MPL
    /// typelist of types.
    template <typename Types> struct GenerateServer {
        typedef typename boost::mpl::begin<Types>::type Begin;
        typedef typename boost::mpl::end<Types>::type End;

        template <typename Iter, bool IsEnd = boost::is_same<Iter, End>::value>
        class ServerElement;

        template <typename Iter> struct ComputeBases {
            typedef typename boost::mpl::deref<Iter>::type LeafBase;
            typedef ServerElement<typename boost::mpl::next<Iter>::type>
                OtherBase;
        };

        template <typename Iter>
        class ServerElement<Iter, false>
            : public ComputeBases<Iter>::LeafBase,
              public ComputeBases<Iter>::OtherBase {
          public:
            typedef typename ComputeBases<Iter>::LeafBase LeafBase;
            typedef typename ComputeBases<Iter>::OtherBase OtherBase;
            GenerateServer(DeviceInitObject &init, vrpn_Connection *conn)
                : LeafBase(init, conn), OtherBase(init, conn) {}
            void mainloop() { LeafBase::server_mainloop(); }
        };

        /// Base case
        template <typename Iter> class ServerElement<Iter, true> {
          public:
            GenerateServer(DeviceInitObject &, vrpn_Connection *) {}
            void mainloop() {}
        };

        /// @brief Computed server type
        typedef ServerElement<Begin> type;

        /// @brief Create a server, returning it in a unique_ptr.
        unique_ptr<type> run(DeviceInitObject &init, vrpn_Connection *conn) {
            return new type(init, conn);
        }
    };

} // namespace connection
} // namespace osvr

#endif // INCLUDED_GenerateCompoundServer_h_GUID_55F870FA_C398_49B8_9907_A007B3C6F8CA
