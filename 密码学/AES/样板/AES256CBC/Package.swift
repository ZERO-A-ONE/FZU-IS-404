// swift-tools-version:5.0
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(name: "AES256CBC")

package.platforms = [.macOS(.v10_12), .iOS(.v11), .tvOS(.v11), .watchOS(.v2)]
package.products = [.library(name: "AES256CBC", targets: ["AES256CBC"])]
package.swiftLanguageVersions = [.v5]
package.targets = [
    .target(name: "AES256CBC", dependencies: [], path: "Sources"),
    .testTarget(name: "AES256CBCTests", dependencies: ["AES256CBC"])
]
