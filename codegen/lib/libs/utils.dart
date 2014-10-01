library fcs.libs.utils;

import 'package:ebisu_cpp/cpp.dart';
import 'package:fcs/installation.dart';

final utils = lib('utils')
  ..namespace = namespace([ 'fcs', 'utils' ])
  ..headers = [
    header('utils')
    ..headers = [ 'cmath', 'iostream' ]
    ..customBlocks = [ fcbPreNamespace, fcbPostNamespace, fcbBeginNamespace, fcbEndNamespace ]
    ..classes = [
      class_('block_indenter')..customBlocks = [ clsPreDecl, clsPublic, clsPostDecl ],
      class_('value_min_max'),
      class_('fixed_size_char_array'),
      class_('version_control_commit'),
      class_('histogram')
      ..customBlocks = [ clsProtected, clsPreDecl ]
      ..template = ['typename T = double', 'typename T2 = int']
      ..members = [
        member('num_bins')..init = 20..access = ro,
        member('results')
        ..type = 'Result_vector_t'..initText = 'Result_vector_t(num_bins_,999)'..access = ro,
        member('pi')..type = 'double'..access = rw..noInit = true,
        member('pid')..type = 'somenumtype'..initText = '(3.14**2.0)'
        ..refType = ref..byRef = true,
        member('goo')..byRef = true..access = rw..init = 'Fooberger',
        member('moo')..init = 'falal'..access = null,
        member('zoo')..init = 'falal'..cppAccess = protected,
      ],
    ]
  ];

addItems() => installation.addLib(utils);

main() {
  addItems();
  installation.generateItems();
}