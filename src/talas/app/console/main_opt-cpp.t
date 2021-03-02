%########################################################################
%# Copyright (c) 1988-2021 $organization$
%#
%# This software is provided by the author and contributors ``as is'' 
%# and any express or implied warranties, including, but not limited to, 
%# the implied warranties of merchantability and fitness for a particular 
%# purpose are disclaimed. In no event shall the author or contributors 
%# be liable for any direct, indirect, incidental, special, exemplary, 
%# or consequential damages (including, but not limited to, procurement 
%# of substitute goods or services; loss of use, data, or profits; or 
%# business interruption) however caused and on any theory of liability, 
%# whether in contract, strict liability, or tort (including negligence 
%# or otherwise) arising in any way out of the use of this software, 
%# even if advised of the possibility of such damage.
%#
%#   File: main_opt-cpp.t
%#
%# Author: $author$
%#   Date: 2/23/2021
%########################################################################
%with(%
%is_include_path,%(%else-then(%is_include_path%,%(%is_Include_path%)%)%)%,%
%include_path,%(%else-then(%if-no(%is_include_path%,,%(%include_path%)%)%,%(%if-no(%is_include_path%,,%(%filepath(%input%)%)%)%)%)%)%,%
%Include_path,%(%else-then(%if-no(%is_include_path%,,%(%Include_path%)%)%,%(%if-no(%is_include_path%,,%(%include_path%)%)%)%)%)%,%
%INCLUDE_PATH,%(%else-then(%INCLUDE_PATH%,%(%toupper(%Include_path%)%)%)%)%,%
%include_path,%(%else-then(%_include_path%,%(%tolower(%Include_path%)%)%)%)%,%
%is_filetypeextension,%(%else-then(%is_filetypeextension%,%(%is_FileTypeExtension%)%)%)%,%
%filetypeextension,%(%else-then(%if-no(%is_filetypeextension%,,%(%filetypeextension%)%)%,%(%if-no(%is_filetypeextension%,,%(cpp)%)%)%)%)%,%
%FileTypeExtension,%(%else-then(%if-no(%is_filetypeextension%,,%(%FileTypeExtension%)%)%,%(%if-no(%is_filetypeextension%,,%(%filetypeextension%)%)%)%)%)%,%
%FILETYPEEXTENSION,%(%else-then(%FILETYPEEXTENSION%,%(%toupper(%FileTypeExtension%)%)%)%)%,%
%filetypeextension,%(%else-then(%_filetypeextension%,%(%tolower(%FileTypeExtension%)%)%)%)%,%
%is_framework,%(%else-then(%is_framework%,%(%is_Framework%)%)%)%,%
%framework,%(%else-then(%if-no(%is_framework%,,%(%framework%)%)%,%(%if-no(%is_framework%,,%(talas)%)%)%)%)%,%
%Framework,%(%else-then(%if-no(%is_framework%,,%(%Framework%)%)%,%(%if-no(%is_framework%,,%(%framework%)%)%)%)%)%,%
%FRAMEWORK,%(%else-then(%FRAMEWORK%,%(%toupper(%Framework%)%)%)%)%,%
%framework,%(%else-then(%_framework%,%(%tolower(%Framework%)%)%)%)%,%
%is_name,%(%else-then(%is_name%,%(%is_Name%)%)%)%,%
%name,%(%else-then(%if-no(%is_name%,,%(%name%)%)%,%(%if-no(%is_name%,,%(main_opt)%)%)%)%)%,%
%Name,%(%else-then(%if-no(%is_name%,,%(%Name%)%)%,%(%if-no(%is_name%,,%(%name%)%)%)%)%)%,%
%NAME,%(%else-then(%NAME%,%(%toupper(%Name%)%)%)%)%,%
%name,%(%else-then(%_name%,%(%tolower(%Name%)%)%)%)%,%
%is_what,%(%else-then(%is_what%,%(%is_What%)%)%)%,%
%what,%(%else-then(%if-no(%is_what%,,%(%what%)%)%,%(%if-no(%is_what%,,%(what)%)%)%)%)%,%
%What,%(%else-then(%if-no(%is_what%,,%(%What%)%)%,%(%if-no(%is_what%,,%(%what%)%)%)%)%)%,%
%WHAT,%(%else-then(%WHAT%,%(%toupper(%What%)%)%)%)%,%
%what,%(%else-then(%_what%,%(%tolower(%What%)%)%)%)%,%
%is_ifndef,%(%else-then(%is_ifndef%,%(%is_Ifndef%)%)%)%,%
%ifndef,%(%else-then(%if-no(%is_ifndef%,,%(%ifndef%)%)%,%(%if-no(%is_ifndef%,,%(%parse(%WHAT%,/,,,_,%(%What%)%,What)%)%)%)%)%)%,%
%Ifndef,%(%else-then(%if-no(%is_ifndef%,,%(%Ifndef%)%)%,%(%if-no(%is_ifndef%,,%(%ifndef%)%)%)%)%)%,%
%IFNDEF,%(%else-then(%IFNDEF%,%(%toupper(%Ifndef%)%)%)%)%,%
%ifndef,%(%else-then(%_ifndef%,%(%tolower(%Ifndef%)%)%)%)%,%
%is_include,%(%else-then(%is_include%,%(%is_Include%)%)%)%,%
%include,%(%else-then(%if-no(%is_include%,,%(%include%)%)%,%(%if-no(%is_include%,,%(%if-then(%What%,/)%)%)%)%)%)%,%
%Include,%(%else-then(%if-no(%is_include%,,%(%Include%)%)%,%(%if-no(%is_include%,,%(%include%)%)%)%)%)%,%
%INCLUDE,%(%else-then(%INCLUDE%,%(%toupper(%Include%)%)%)%)%,%
%include,%(%else-then(%_include%,%(%tolower(%Include%)%)%)%)%,%
%is_namespace,%(%else-then(%is_namespace%,%(%is_Namespace%)%)%)%,%
%namespace,%(%else-then(%if-no(%is_namespace%,,%(%namespace%)%)%,%(%if-no(%is_namespace%,,%(%What%)%)%)%)%)%,%
%Namespace,%(%else-then(%if-no(%is_namespace%,,%(%Namespace%)%)%,%(%if-no(%is_namespace%,,%(%namespace%)%)%)%)%)%,%
%NAMESPACE,%(%else-then(%NAMESPACE%,%(%toupper(%Namespace%)%)%)%)%,%
%namespace,%(%else-then(%_namespace%,%(%tolower(%Namespace%)%)%)%)%,%
%is_namespace_begin,%(%else-then(%is_namespace_begin%,%(%is_Namespace_begin%)%)%)%,%
%namespace_begin,%(%else-then(%if-no(%is_namespace_begin%,,%(%namespace_begin%)%)%,%(%if-no(%is_namespace_begin%,,%(%parse(%Namespace%,/,,,,%(
namespace %ns% {)%,ns)%)%)%)%)%)%,%
%Namespace_begin,%(%else-then(%if-no(%is_namespace_begin%,,%(%Namespace_begin%)%)%,%(%if-no(%is_namespace_begin%,,%(%namespace_begin%)%)%)%)%)%,%
%NAMESPACE_BEGIN,%(%else-then(%NAMESPACE_BEGIN%,%(%toupper(%Namespace_begin%)%)%)%)%,%
%namespace_begin,%(%else-then(%_namespace_begin%,%(%tolower(%Namespace_begin%)%)%)%)%,%
%is_namespace_end,%(%else-then(%is_namespace_end%,%(%is_Namespace_end%)%)%)%,%
%namespace_end,%(%else-then(%if-no(%is_namespace_end%,,%(%namespace_end%)%)%,%(%if-no(%is_namespace_end%,,%(%reverse-parse(%Namespace%,/,,,,%(} /// namespace %ns%
)%,ns)%)%)%)%)%)%,%
%Namespace_end,%(%else-then(%if-no(%is_namespace_end%,,%(%Namespace_end%)%)%,%(%if-no(%is_namespace_end%,,%(%namespace_end%)%)%)%)%)%,%
%NAMESPACE_END,%(%else-then(%NAMESPACE_END%,%(%toupper(%Namespace_end%)%)%)%)%,%
%namespace_end,%(%else-then(%_namespace_end%,%(%tolower(%Namespace_end%)%)%)%)%,%
%%(%
%%include(%Include_path%/file-hpp-cpp.t)%%
%#include "talas/app/console/%Include%main_opt.hpp"

namespace talas {
namespace app {
namespace console {%namespace_begin%

///////////////////////////////////////////////////////////////////////
/// class main_optt
///////////////////////////////////////////////////////////////////////
#if defined(TALAS_APP_CONSOLE_%IFNDEF%MAIN_OPT_INSTANCE)
static main_opt the_main_opt;
#endif /// defined(TALAS_APP_CONSOLE_%IFNDEF%MAIN_OPT_INSTANCE) 

%namespace_end%} /// namespace console 
} /// namespace app 
} /// namespace talas 
%
%)%)%