/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eej-jama <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 21:14:28 by hlakhal-          #+#    #+#             */
/*   Updated: 2024/02/13 18:14:24 by eej-jama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
#define LOCATION_HPP
#include <vector>
#include <map>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include <stdexcept>

class Location
{
    protected:
        std::vector<std::pair<std::string, std::string> > locationPairs;
        std::string path;
        std::string auto_index;
        std::string  root;
        std::string  upload;
        std::string listingDir;
        std::vector<std::string> methods;
        std::vector<std::string> index;
        std::map<std::string, std::string> cgi_path;
        std::string  redirectPath;
        std::string  UploadPath;
    public:
        Location();
        Location(std::string root);
        const Location& getLocation() const;
        Location* createLocation();
        class ErrorLocation: public std::runtime_error
        {
            public:
                ErrorLocation(const std::string& message);
        };
        void setPath(std::string& path);
        void setAutoIndex(std::string& AutoIndex);
        void setMethods(std::string& Methods);
        void setIndex(std::string& index);
        void setCgi(std::string& CgiPath);
        void setRoot(std::string& root);
        void setRedirect(std::string& path);
        void setUpload(std::string& upload);
        void setListingDir(std::string& linting);
        void setUploadPath(std::string& path);
        const std::map<std::string, std::string>& getCgiPath() const;
        std::string getPath() const;
        const std::vector<std::string>& getIndexes() const;
        std::string getAutoIndex() const;
        std::string getRedirect() const;
        std::string getRoot() const;
        const std::string& getUpload() const;
        const std::string& getListingDir() const;
        const std::vector<std::string>& getMethods() const;
        const std::string& getUploadPath() const;
        ~Location();
};

#endif
