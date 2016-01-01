# NetworkActiv Data Manipulation Plugin

This project creates a Windows DLL file that enables programs such as NetworkActiv AUTAPF to manipulate network data as it is forwarded. Because AUTAPF is static-built, this plugin has been designed to be built static as well.

### Features

* Allows binary or text within packets to be replaced with different binary or text.
* Allows the resulting data to be of a different length from the original data.
* Allows the client to be disconnected if unsuitable data is found.
* Enables manipulation of both *Downstream* (server-to-client) and *Upstream* (client-to-server) data channels.
* Uses JSON for plugin settings.
* Written in C++ for maximum performance. Both 32-bit and 64-bit builds are supported.
* Statically-built for minimal post-build dependency.
* Exports \*Cmd versions of the functions for troubleshooting via *rundll32*. For example: *rundll32 NA_Plugin_DataManipulation_x64.dll,ProcessDownstreamDataCmd "This is text to be modified."*

### Licence

This plugin is distributed under the standard MIT licence. See LICENCE.TXT for details. As a result of this licence, you may use this plugin in your own projects.

The linked packages have their own respective licences, so be sure to look into these licences as appropriate.

### Copyright

The initial commit of this plugin (minus dependencies) was designed and written entirely by Michael J. Kowalski of [NetworkActiv Software].

### Dependencies

* [rapidjson] -- used to parse JSON loaded from local settings file.

### Building the DLL

This project was designed to be opened and built using [Microsoft Visual Studio 2015]. You will need to make sure that rapidjson is added to the project, such as through NuGet. **This project must be built statically if it will be used with NetworkActiv AUTAPF or PortImport**.

### Contributions

Additions are welcome as long as they are well-coded, not too specific to a particular product or service, and appropriately licensed. Any contributions must be made under the MIT licence or in Public Domain. Copy-left contributions cannot be accepted. No guarantee is given as to whether a particular contribution will be accepted.

   [Microsoft Visual Studio 2015]: <https://www.visualstudio.com/en-us/products/visual-studio-community-vs.aspx>
   [rapidjson]: <https://github.com/miloyip/rapidjson>
   [NetworkActiv Software]: <https://www.networkactiv.com/>