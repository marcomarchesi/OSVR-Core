/** @file
    @brief Implementation

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

// Internal Includes
#include <osvr/Routing/RouteContainer.h>
#include <osvr/Routing/RoutingKeys.h>

// Library/third-party includes
#include <json/value.h>
#include <json/reader.h>
#include <json/writer.h>

// Standard includes
#include <stdexcept>
#include <functional>
#include <algorithm>

namespace osvr {
namespace routing {

    static inline Json::Value
    parseRoutingDirective(std::string const &routingDirective) {
        Json::Reader reader;
        Json::Value val;
        if (!reader.parse(routingDirective, val)) {
            throw std::runtime_error("Invalid JSON routing directive: " +
                                     routingDirective);
        }
        return val;
    }

    static inline std::string
    getDestination(Json::Value const &routingDirective) {
        return routingDirective.get(keys::destination(), "").asString();
    }
    static inline std::string toFastString(Json::Value const &val) {
        Json::FastWriter writer;
        return writer.write(val);
    }
    RouteContainer::RouteContainer() {}

    RouteContainer::RouteContainer(std::string const &routes) {
        Json::Reader reader;
        Json::Value routesVal;
        if (!reader.parse(routes, routesVal)) {
            throw std::runtime_error("Invalid JSON routing directive array: " +
                                     routes);
        }
        for (Json::ArrayIndex i = 0, e = routesVal.size(); i < e; ++i) {
            const Json::Value thisRoute = routesVal[i];
            m_addRoute(getDestination(thisRoute), toFastString(thisRoute));
        }
    }

    bool RouteContainer::addRoute(std::string const &routingDirective) {
        auto route = parseRoutingDirective(routingDirective);
        return m_addRoute(getDestination(route), routingDirective);
    }

    std::string RouteContainer::getRoutes(bool styled) const {
        Json::Value routes(Json::arrayValue);
        for (auto const &r : m_routingDirectives) {
            routes.append(parseRoutingDirective(r));
        }
        if (styled) {
            return routes.toStyledString();
        } else {
            return toFastString(routes);
        }
    }

    std::string
    RouteContainer::getSource(std::string const &destination) const {
        auto route = getRouteForDestination(destination);
        if (!route.empty()) {
            Json::Value directive = parseRoutingDirective(route);
            if (directive.isMember(keys::source())) {
                return directive[keys::source()].toStyledString();
            }
        }
        return std::string();
    }

    std::string RouteContainer::getRouteForDestination(
        std::string const &destination) const {
        auto it =
            std::find_if(begin(m_routingDirectives), end(m_routingDirectives),
                         [&](std::string const &directive) {
            return (getDestination(parseRoutingDirective(directive)) ==
                    destination);
        });
        if (it != end(m_routingDirectives)) {
            return *it;
        }
        return std::string();
    }

    bool RouteContainer::m_addRoute(std::string const &destination,
                                    std::string const &routingDirective) {
        bool replaced = false;
        /// If a route already exists with the same destination, replace it
        /// with this new one.
        std::replace_if(
            begin(m_routingDirectives),
            end(m_routingDirectives), [&](std::string const &directive) {
            Json::Value candidate = parseRoutingDirective(directive);
            bool match = (getDestination(candidate) == destination);
            if (match) {
                replaced = true;
            }
            return match;
        }, routingDirective);

        /// If we didn't replace an existing route, just add this one.
        if (!replaced) {
            m_routingDirectives.push_back(routingDirective);
        }
        return !replaced;
    }
} // namespace routing
} // namespace osvr