import Foundation
import PackagePlugin

@main
struct CodeFormatter: CommandPlugin {
    
    func performCommand(
      context: PackagePlugin.PluginContext,
      arguments: [String]
    ) async throws {
        print(#file)
        print(#filePath)
    }

}
