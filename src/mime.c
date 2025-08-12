#include "../properties.h"
#if GET_MIME_TYPE
#include "mime.h"

#include <string.h>

static int equal(const char* str1, const char* str2);

const char* mime_get_type(const char* ext) {
    /* Check for NULL */
    if (!ext) return "application/octet-stream";

    /* MIME types */
    if (equal(ext, "123"))
        return "application/vnd.lotus-1-2-3";
    if (equal(ext, "1km"))
        return "application/vnd.1000minds.decision-model+xml";
    if (equal(ext, "210"))
        return "model/step";
    if (equal(ext, "3dml"))
        return "text/vnd.in3d.3dml charset=UTF-8";
    if (equal(ext, "3ds"))
        return "image/x-3ds";
    if (equal(ext, "3g2"))
        return "video/3gpp2";
    if (equal(ext, "3gp"))
        return "video/3gpp";
    if (equal(ext, "3gpp"))
        return "audio/3gpp";
    if (equal(ext, "3mf"))
        return "model/3mf";
    if (equal(ext, "7z"))
        return "application/x-7z-compressed";
    if (equal(ext, "aab"))
        return "application/x-authorware-bin";
    if (equal(ext, "aac"))
        return "audio/aac";
    if (equal(ext, "aam"))
        return "application/x-authorware-map";
    if (equal(ext, "aas"))
        return "application/x-authorware-seg";
    if (equal(ext, "abw"))
        return "application/x-abiword";
    if (equal(ext, "ac"))
        return "application/pkix-attr-cert";
    if (equal(ext, "acc"))
        return "application/vnd.americandynamics.acc";
    if (equal(ext, "ace"))
        return "application/x-ace-compressed";
    if (equal(ext, "acu"))
        return "application/vnd.acucobol";
    if (equal(ext, "acutc"))
        return "application/vnd.acucorp";
    if (equal(ext, "adp"))
        return "audio/adpcm";
    if (equal(ext, "adts"))
        return "audio/aac";
    if (equal(ext, "aep"))
        return "application/vnd.audiograph";
    if (equal(ext, "afm"))
        return "application/x-font-type1";
    if (equal(ext, "afp"))
        return "application/vnd.ibm.modcap";
    if (equal(ext, "age"))
        return "application/vnd.age";
    if (equal(ext, "ahead"))
        return "application/vnd.ahead.space";
    if (equal(ext, "ai"))
        return "application/postscript";
    if (equal(ext, "aif"))
        return "audio/x-aiff";
    if (equal(ext, "aifc"))
        return "audio/x-aiff";
    if (equal(ext, "aiff"))
        return "audio/x-aiff";
    if (equal(ext, "air"))
        return "application/vnd.adobe.air-application-installer-package+zip";
    if (equal(ext, "ait"))
        return "application/vnd.dvb.ait";
    if (equal(ext, "ami"))
        return "application/vnd.amiga.ami";
    if (equal(ext, "aml"))
        return "application/automationml-aml+xml";
    if (equal(ext, "amlx"))
        return "application/automationml-amlx+zip";
    if (equal(ext, "amr"))
        return "audio/amr";
    if (equal(ext, "apk"))
        return "application/vnd.android.package-archive";
    if (equal(ext, "apng"))
        return "image/apng";
    if (equal(ext, "appcache"))
        return "text/cache-manifest charset=UTF-8";
    if (equal(ext, "appinstaller"))
        return "application/appinstaller";
    if (equal(ext, "application"))
        return "application/x-ms-application";
    if (equal(ext, "appx"))
        return "application/appx";
    if (equal(ext, "appxbundle"))
        return "application/appxbundle";
    if (equal(ext, "apr"))
        return "application/vnd.lotus-approach";
    if (equal(ext, "arc"))
        return "application/x-freearc";
    if (equal(ext, "arj"))
        return "application/x-arj";
    if (equal(ext, "asc"))
        return "application/pgp-keys";
    if (equal(ext, "asf"))
        return "video/x-ms-asf";
    if (equal(ext, "asm"))
        return "text/x-asm charset=UTF-8";
    if (equal(ext, "aso"))
        return "application/vnd.accpac.simply.aso";
    if (equal(ext, "asx"))
        return "video/x-ms-asf";
    if (equal(ext, "atc"))
        return "application/vnd.acucorp";
    if (equal(ext, "atom"))
        return "application/atom+xml";
    if (equal(ext, "atomcat"))
        return "application/atomcat+xml";
    if (equal(ext, "atomdeleted"))
        return "application/atomdeleted+xml";
    if (equal(ext, "atomsvc"))
        return "application/atomsvc+xml";
    if (equal(ext, "atx"))
        return "application/vnd.antix.game-component";
    if (equal(ext, "au"))
        return "audio/basic";
    if (equal(ext, "avci"))
        return "image/avci";
    if (equal(ext, "avcs"))
        return "image/avcs";
    if (equal(ext, "avi"))
        return "video/x-msvideo";
    if (equal(ext, "avif"))
        return "image/avif";
    if (equal(ext, "aw"))
        return "application/applixware";
    if (equal(ext, "azf"))
        return "application/vnd.airzip.filesecure.azf";
    if (equal(ext, "azs"))
        return "application/vnd.airzip.filesecure.azs";
    if (equal(ext, "azv"))
        return "image/vnd.airzip.accelerator.azv";
    if (equal(ext, "azw"))
        return "application/vnd.amazon.ebook";
    if (equal(ext, "b16"))
        return "image/vnd.pco.b16";
    if (equal(ext, "bary"))
        return "model/vnd.bary";
    if (equal(ext, "bat"))
        return "application/x-msdownload";
    if (equal(ext, "bcpio"))
        return "application/x-bcpio";
    if (equal(ext, "bdf"))
        return "application/x-font-bdf";
    if (equal(ext, "bdm"))
        return "application/vnd.syncml.dm+wbxml";
    if (equal(ext, "bdo"))
        return "application/vnd.nato.bindingdataobject+xml";
    if (equal(ext, "bdoc"))
        return "application/bdoc";
    if (equal(ext, "bed"))
        return "application/vnd.realvnc.bed";
    if (equal(ext, "bh2"))
        return "application/vnd.fujitsu.oasysprs";
    if (equal(ext, "bin"))
        return "application/octet-stream";
    if (equal(ext, "blb"))
        return "application/x-blorb";
    if (equal(ext, "blend"))
        return "application/x-blender";
    if (equal(ext, "blorb"))
        return "application/x-blorb";
    if (equal(ext, "bmi"))
        return "application/vnd.bmi";
    if (equal(ext, "bmml"))
        return "application/vnd.balsamiq.bmml+xml";
    if (equal(ext, "bmp"))
        return "image/bmp";
    if (equal(ext, "book"))
        return "application/vnd.framemaker";
    if (equal(ext, "box"))
        return "application/vnd.previewsystems.box";
    if (equal(ext, "boz"))
        return "application/x-bzip2";
    if (equal(ext, "bpk"))
        return "application/octet-stream";
    if (equal(ext, "brush"))
        return "application/vnd.procreate.brush";
    if (equal(ext, "brushset"))
        return "application/vnd.procrate.brushset";
    if (equal(ext, "bsp"))
        return "model/vnd.valve.source.compiled-map";
    if (equal(ext, "btf"))
        return "image/prs.btif";
    if (equal(ext, "btif"))
        return "image/prs.btif";
    if (equal(ext, "buffer"))
        return "application/octet-stream";
    if (equal(ext, "bz"))
        return "application/x-bzip";
    if (equal(ext, "bz2"))
        return "application/x-bzip2";
    if (equal(ext, "c"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "c11amc"))
        return "application/vnd.cluetrust.cartomobile-config";
    if (equal(ext, "c11amz"))
        return "application/vnd.cluetrust.cartomobile-config-pkg";
    if (equal(ext, "c4d"))
        return "application/vnd.clonk.c4group";
    if (equal(ext, "c4f"))
        return "application/vnd.clonk.c4group";
    if (equal(ext, "c4g"))
        return "application/vnd.clonk.c4group";
    if (equal(ext, "c4p"))
        return "application/vnd.clonk.c4group";
    if (equal(ext, "c4u"))
        return "application/vnd.clonk.c4group";
    if (equal(ext, "cab"))
        return "application/vnd.ms-cab-compressed";
    if (equal(ext, "caf"))
        return "audio/x-caf";
    if (equal(ext, "cap"))
        return "application/vnd.tcpdump.pcap";
    if (equal(ext, "car"))
        return "application/vnd.curl.car";
    if (equal(ext, "cat"))
        return "application/vnd.ms-pki.seccat";
    if (equal(ext, "cb7"))
        return "application/x-cbr";
    if (equal(ext, "cba"))
        return "application/x-cbr";
    if (equal(ext, "cbr"))
        return "application/x-cbr";
    if (equal(ext, "cbt"))
        return "application/x-cbr";
    if (equal(ext, "cbz"))
        return "application/x-cbr";
    if (equal(ext, "cc"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "cco"))
        return "application/x-cocoa";
    if (equal(ext, "cct"))
        return "application/x-director";
    if (equal(ext, "ccxml"))
        return "application/ccxml+xml";
    if (equal(ext, "cdbcmsg"))
        return "application/vnd.contact.cmsg";
    if (equal(ext, "cdf"))
        return "application/x-netcdf";
    if (equal(ext, "cdfx"))
        return "application/cdfx+xml";
    if (equal(ext, "cdkey"))
        return "application/vnd.mediastation.cdkey";
    if (equal(ext, "cdmia"))
        return "application/cdmi-capability";
    if (equal(ext, "cdmic"))
        return "application/cdmi-container";
    if (equal(ext, "cdmid"))
        return "application/cdmi-domain";
    if (equal(ext, "cdmio"))
        return "application/cdmi-object";
    if (equal(ext, "cdmiq"))
        return "application/cdmi-queue";
    if (equal(ext, "cdx"))
        return "chemical/x-cdx";
    if (equal(ext, "cdxml"))
        return "application/vnd.chemdraw+xml";
    if (equal(ext, "cdy"))
        return "application/vnd.cinderella";
    if (equal(ext, "cer"))
        return "application/pkix-cert";
    if (equal(ext, "cfs"))
        return "application/x-cfs-compressed";
    if (equal(ext, "cgm"))
        return "image/cgm";
    if (equal(ext, "chat"))
        return "application/x-chat";
    if (equal(ext, "chm"))
        return "application/vnd.ms-htmlhelp";
    if (equal(ext, "chrt"))
        return "application/vnd.kde.kchart";
    if (equal(ext, "cif"))
        return "chemical/x-cif";
    if (equal(ext, "cii"))
        return "application/vnd.anser-web-certificate-issue-initiation";
    if (equal(ext, "cil"))
        return "application/vnd.ms-artgalry";
    if (equal(ext, "cjs"))
        return "application/node";
    if (equal(ext, "cla"))
        return "application/vnd.claymore";
    if (equal(ext, "class"))
        return "application/java-vm";
    if (equal(ext, "cld"))
        return "model/vnd.cld";
    if (equal(ext, "clkk"))
        return "application/vnd.crick.clicker.keyboard";
    if (equal(ext, "clkp"))
        return "application/vnd.crick.clicker.palette";
    if (equal(ext, "clkt"))
        return "application/vnd.crick.clicker.template";
    if (equal(ext, "clkw"))
        return "application/vnd.crick.clicker.wordbank";
    if (equal(ext, "clkx"))
        return "application/vnd.crick.clicker";
    if (equal(ext, "clp"))
        return "application/x-msclip";
    if (equal(ext, "cmc"))
        return "application/vnd.cosmocaller";
    if (equal(ext, "cmdf"))
        return "chemical/x-cmdf";
    if (equal(ext, "cml"))
        return "chemical/x-cml";
    if (equal(ext, "cmp"))
        return "application/vnd.yellowriver-custom-menu";
    if (equal(ext, "cmx"))
        return "image/x-cmx";
    if (equal(ext, "cod"))
        return "application/vnd.rim.cod";
    if (equal(ext, "coffee"))
        return "text/coffeescript charset=UTF-8";
    if (equal(ext, "com"))
        return "application/x-msdownload";
    if (equal(ext, "conf"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "cpio"))
        return "application/x-cpio";
    if (equal(ext, "cpl"))
        return "application/cpl+xml";
    if (equal(ext, "cpp"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "cpt"))
        return "application/mac-compactpro";
    if (equal(ext, "crd"))
        return "application/x-mscardfile";
    if (equal(ext, "crl"))
        return "application/pkix-crl";
    if (equal(ext, "crt"))
        return "application/x-x509-ca-cert";
    if (equal(ext, "crx"))
        return "application/x-chrome-extension";
    if (equal(ext, "cryptonote"))
        return "application/vnd.rig.cryptonote";
    if (equal(ext, "csh"))
        return "application/x-csh";
    if (equal(ext, "csl"))
        return "application/vnd.citationstyles.style+xml";
    if (equal(ext, "csml"))
        return "chemical/x-csml";
    if (equal(ext, "csp"))
        return "application/vnd.commonspace";
    if (equal(ext, "css"))
        return "text/css charset=UTF-8";
    if (equal(ext, "cst"))
        return "application/x-director";
    if (equal(ext, "csv"))
        return "text/csv charset=UTF-8";
    if (equal(ext, "cu"))
        return "application/cu-seeme";
    if (equal(ext, "curl"))
        return "text/vnd.curl charset=UTF-8";
    if (equal(ext, "cwl"))
        return "application/cwl";
    if (equal(ext, "cww"))
        return "application/prs.cww";
    if (equal(ext, "cxt"))
        return "application/x-director";
    if (equal(ext, "cxx"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "dae"))
        return "model/vnd.collada+xml";
    if (equal(ext, "daf"))
        return "application/vnd.mobius.daf";
    if (equal(ext, "dart"))
        return "application/vnd.dart";
    if (equal(ext, "dataless"))
        return "application/vnd.fdsn.seed";
    if (equal(ext, "davmount"))
        return "application/davmount+xml";
    if (equal(ext, "dbf"))
        return "application/vnd.dbf";
    if (equal(ext, "dbk"))
        return "application/docbook+xml";
    if (equal(ext, "dcm"))
        return "application/dicom";
    if (equal(ext, "dcmp"))
        return "application/vnd.dcmp+xml";
    if (equal(ext, "dcr"))
        return "application/x-director";
    if (equal(ext, "dcurl"))
        return "text/vnd.curl.dcurl charset=UTF-8";
    if (equal(ext, "dd2"))
        return "application/vnd.oma.dd2+xml";
    if (equal(ext, "ddd"))
        return "application/vnd.fujixerox.ddd";
    if (equal(ext, "ddf"))
        return "application/vnd.syncml.dmddf+xml";
    if (equal(ext, "dds"))
        return "image/vnd.ms-dds";
    if (equal(ext, "deb"))
        return "application/octet-stream";
    if (equal(ext, "def"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "deploy"))
        return "application/octet-stream";
    if (equal(ext, "der"))
        return "application/x-x509-ca-cert";
    if (equal(ext, "dfac"))
        return "application/vnd.dreamfactory";
    if (equal(ext, "dgc"))
        return "application/x-dgc-compressed";
    if (equal(ext, "dib"))
        return "image/bmp";
    if (equal(ext, "dic"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "dir"))
        return "application/x-director";
    if (equal(ext, "dis"))
        return "application/vnd.mobius.dis";
    if (equal(ext, "disposition-notification"))
        return "message/disposition-notification";
    if (equal(ext, "dist"))
        return "application/octet-stream";
    if (equal(ext, "distz"))
        return "application/octet-stream";
    if (equal(ext, "djv"))
        return "image/vnd.djvu";
    if (equal(ext, "djvu"))
        return "image/vnd.djvu";
    if (equal(ext, "dll"))
        return "application/octet-stream";
    if (equal(ext, "dmg"))
        return "application/octet-stream";
    if (equal(ext, "dmp"))
        return "application/vnd.tcpdump.pcap";
    if (equal(ext, "dms"))
        return "application/octet-stream";
    if (equal(ext, "dna"))
        return "application/vnd.dna";
    if (equal(ext, "dng"))
        return "image/x-adobe-dng";
    if (equal(ext, "doc"))
        return "application/msword";
    if (equal(ext, "docm"))
        return "application/vnd.ms-word.document.macroenabled.12";
    if (equal(ext, "docx"))
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    if (equal(ext, "dot"))
        return "application/msword";
    if (equal(ext, "dotm"))
        return "application/vnd.ms-word.template.macroenabled.12";
    if (equal(ext, "dotx"))
        return "application/vnd.openxmlformats-officedocument.wordprocessingml.template";
    if (equal(ext, "dp"))
        return "application/vnd.osgi.dp";
    if (equal(ext, "dpg"))
        return "application/vnd.dpgraph";
    if (equal(ext, "dpx"))
        return "image/dpx";
    if (equal(ext, "dra"))
        return "audio/vnd.dra";
    if (equal(ext, "drle"))
        return "image/dicom-rle";
    if (equal(ext, "drm"))
        return "application/vnd.procreate.dream";
    if (equal(ext, "dsc"))
        return "text/prs.lines.tag charset=UTF-8";
    if (equal(ext, "dssc"))
        return "application/dssc+der";
    if (equal(ext, "dtb"))
        return "application/x-dtbook+xml";
    if (equal(ext, "dtd"))
        return "application/xml-dtd";
    if (equal(ext, "dts"))
        return "audio/vnd.dts";
    if (equal(ext, "dtshd"))
        return "audio/vnd.dts.hd";
    if (equal(ext, "dump"))
        return "application/octet-stream";
    if (equal(ext, "dvb"))
        return "video/vnd.dvb.file";
    if (equal(ext, "dvi"))
        return "application/x-dvi";
    if (equal(ext, "dwd"))
        return "application/atsc-dwd+xml";
    if (equal(ext, "dwf"))
        return "model/vnd.dwf";
    if (equal(ext, "dwg"))
        return "image/vnd.dwg";
    if (equal(ext, "dxf"))
        return "image/vnd.dxf";
    if (equal(ext, "dxp"))
        return "application/vnd.spotfire.dxp";
    if (equal(ext, "dxr"))
        return "application/x-director";
    if (equal(ext, "ear"))
        return "application/java-archive";
    if (equal(ext, "ecelp4800"))
        return "audio/vnd.nuera.ecelp4800";
    if (equal(ext, "ecelp7470"))
        return "audio/vnd.nuera.ecelp7470";
    if (equal(ext, "ecelp9600"))
        return "audio/vnd.nuera.ecelp9600";
    if (equal(ext, "ecma"))
        return "application/ecmascript";
    if (equal(ext, "edm"))
        return "application/vnd.novadigm.edm";
    if (equal(ext, "edx"))
        return "application/vnd.novadigm.edx";
    if (equal(ext, "efif"))
        return "application/vnd.picsel";
    if (equal(ext, "ei6"))
        return "application/vnd.pg.osasli";
    if (equal(ext, "elc"))
        return "application/octet-stream";
    if (equal(ext, "emf"))
        return "application/x-msmetafile";
    if (equal(ext, "eml"))
        return "message/rfc822";
    if (equal(ext, "emma"))
        return "application/emma+xml";
    if (equal(ext, "emotionml"))
        return "application/emotionml+xml";
    if (equal(ext, "emz"))
        return "application/x-msmetafile";
    if (equal(ext, "eol"))
        return "audio/vnd.digital-winds";
    if (equal(ext, "eot"))
        return "application/vnd.ms-fontobject";
    if (equal(ext, "eps"))
        return "application/postscript";
    if (equal(ext, "epub"))
        return "application/epub+zip";
    if (equal(ext, "es3"))
        return "application/vnd.eszigno3+xml";
    if (equal(ext, "esa"))
        return "application/vnd.osgi.subsystem";
    if (equal(ext, "esf"))
        return "application/vnd.epson.esf";
    if (equal(ext, "et3"))
        return "application/vnd.eszigno3+xml";
    if (equal(ext, "etx"))
        return "text/x-setext charset=UTF-8";
    if (equal(ext, "eva"))
        return "application/x-eva";
    if (equal(ext, "evy"))
        return "application/x-envoy";
    if (equal(ext, "exe"))
        return "application/octet-stream";
    if (equal(ext, "exi"))
        return "application/exi";
    if (equal(ext, "exp"))
        return "application/express";
    if (equal(ext, "exr"))
        return "image/aces";
    if (equal(ext, "ext"))
        return "application/vnd.novadigm.ext";
    if (equal(ext, "ez"))
        return "application/andrew-inset";
    if (equal(ext, "ez2"))
        return "application/vnd.ezpix-album";
    if (equal(ext, "ez3"))
        return "application/vnd.ezpix-package";
    if (equal(ext, "f"))
        return "text/x-fortran charset=UTF-8";
    if (equal(ext, "f4v"))
        return "video/x-f4v";
    if (equal(ext, "f77"))
        return "text/x-fortran charset=UTF-8";
    if (equal(ext, "f90"))
        return "text/x-fortran charset=UTF-8";
    if (equal(ext, "fbs"))
        return "image/vnd.fastbidsheet";
    if (equal(ext, "fbx"))
        return "application/vnd.autodesk.fbx";
    if (equal(ext, "fcdt"))
        return "application/vnd.adobe.formscentral.fcdt";
    if (equal(ext, "fcs"))
        return "application/vnd.isac.fcs";
    if (equal(ext, "fdf"))
        return "application/fdf";
    if (equal(ext, "fdt"))
        return "application/fdt+xml";
    if (equal(ext, "fe_launch"))
        return "application/vnd.denovo.fcselayout-link";
    if (equal(ext, "fg5"))
        return "application/vnd.fujitsu.oasysgp";
    if (equal(ext, "fgd"))
        return "application/x-director";
    if (equal(ext, "fh"))
        return "image/x-freehand";
    if (equal(ext, "fh4"))
        return "image/x-freehand";
    if (equal(ext, "fh5"))
        return "image/x-freehand";
    if (equal(ext, "fh7"))
        return "image/x-freehand";
    if (equal(ext, "fhc"))
        return "image/x-freehand";
    if (equal(ext, "fig"))
        return "application/x-xfig";
    if (equal(ext, "fits"))
        return "image/fits";
    if (equal(ext, "flac"))
        return "audio/x-flac";
    if (equal(ext, "fli"))
        return "video/x-fli";
    if (equal(ext, "flo"))
        return "application/vnd.micrografx.flo";
    if (equal(ext, "flv"))
        return "video/x-flv";
    if (equal(ext, "flw"))
        return "application/vnd.kde.kivio";
    if (equal(ext, "flx"))
        return "text/vnd.fmi.flexstor charset=UTF-8";
    if (equal(ext, "fly"))
        return "text/vnd.fly charset=UTF-8";
    if (equal(ext, "fm"))
        return "application/vnd.framemaker";
    if (equal(ext, "fnc"))
        return "application/vnd.frogans.fnc";
    if (equal(ext, "fo"))
        return "application/vnd.software602.filler.form+xml";
    if (equal(ext, "for"))
        return "text/x-fortran charset=UTF-8";
    if (equal(ext, "fpx"))
        return "image/vnd.fpx";
    if (equal(ext, "frame"))
        return "application/vnd.framemaker";
    if (equal(ext, "fsc"))
        return "application/vnd.fsc.weblaunch";
    if (equal(ext, "fst"))
        return "image/vnd.fst";
    if (equal(ext, "ftc"))
        return "application/vnd.fluxtime.clip";
    if (equal(ext, "fti"))
        return "application/vnd.anser-web-funds-transfer-initiation";
    if (equal(ext, "fvt"))
        return "video/vnd.fvt";
    if (equal(ext, "fxp"))
        return "application/vnd.adobe.fxp";
    if (equal(ext, "fxpl"))
        return "application/vnd.adobe.fxp";
    if (equal(ext, "fzs"))
        return "application/vnd.fuzzysheet";
    if (equal(ext, "g2w"))
        return "application/vnd.geoplan";
    if (equal(ext, "g3"))
        return "image/g3fax";
    if (equal(ext, "g3w"))
        return "application/vnd.geospace";
    if (equal(ext, "gac"))
        return "application/vnd.groove-account";
    if (equal(ext, "gam"))
        return "application/x-tads";
    if (equal(ext, "gbr"))
        return "application/rpki-ghostbusters";
    if (equal(ext, "gca"))
        return "application/x-gca-compressed";
    if (equal(ext, "gdl"))
        return "model/vnd.gdl";
    if (equal(ext, "gdoc"))
        return "application/vnd.google-apps.document";
    if (equal(ext, "gdraw"))
        return "application/vnd.google-apps.drawing";
    if (equal(ext, "ged"))
        return "text/vnd.familysearch.gedcom charset=UTF-8";
    if (equal(ext, "geo"))
        return "application/vnd.dynageo";
    if (equal(ext, "geojson"))
        return "application/geo+json";
    if (equal(ext, "gex"))
        return "application/vnd.geometry-explorer";
    if (equal(ext, "gform"))
        return "application/vnd.google-apps.form";
    if (equal(ext, "ggb"))
        return "application/vnd.geogebra.file";
    if (equal(ext, "ggs"))
        return "application/vnd.geogebra.slides";
    if (equal(ext, "ggt"))
        return "application/vnd.geogebra.tool";
    if (equal(ext, "ghf"))
        return "application/vnd.groove-help";
    if (equal(ext, "gif"))
        return "image/gif";
    if (equal(ext, "gim"))
        return "application/vnd.groove-identity-message";
    if (equal(ext, "gjam"))
        return "application/vnd.google-apps.jam";
    if (equal(ext, "glb"))
        return "model/gltf-binary";
    if (equal(ext, "gltf"))
        return "model/gltf+json";
    if (equal(ext, "gmap"))
        return "application/vnd.google-apps.map";
    if (equal(ext, "gml"))
        return "application/gml+xml";
    if (equal(ext, "gmx"))
        return "application/vnd.gmx";
    if (equal(ext, "gnumeric"))
        return "application/x-gnumeric";
    if (equal(ext, "gph"))
        return "application/vnd.flographit";
    if (equal(ext, "gpx"))
        return "application/gpx+xml";
    if (equal(ext, "gqf"))
        return "application/vnd.grafeq";
    if (equal(ext, "gqs"))
        return "application/vnd.grafeq";
    if (equal(ext, "gram"))
        return "application/srgs";
    if (equal(ext, "gramps"))
        return "application/x-gramps-xml";
    if (equal(ext, "gre"))
        return "application/vnd.geometry-explorer";
    if (equal(ext, "grv"))
        return "application/vnd.groove-injector";
    if (equal(ext, "grxml"))
        return "application/srgs+xml";
    if (equal(ext, "gscript"))
        return "application/vnd.google-apps.script";
    if (equal(ext, "gsf"))
        return "application/x-font-ghostscript";
    if (equal(ext, "gsheet"))
        return "application/vnd.google-apps.spreadsheet";
    if (equal(ext, "gsite"))
        return "application/vnd.google-apps.site";
    if (equal(ext, "gslides"))
        return "application/vnd.google-apps.presentation";
    if (equal(ext, "gtar"))
        return "application/x-gtar";
    if (equal(ext, "gtm"))
        return "application/vnd.groove-tool-message";
    if (equal(ext, "gtw"))
        return "model/vnd.gtw";
    if (equal(ext, "gv"))
        return "text/vnd.graphviz charset=UTF-8";
    if (equal(ext, "gxf"))
        return "application/gxf";
    if (equal(ext, "gxt"))
        return "application/vnd.geonext";
    if (equal(ext, "gz"))
        return "application/gzip";
    if (equal(ext, "h"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "h261"))
        return "video/h261";
    if (equal(ext, "h263"))
        return "video/h263";
    if (equal(ext, "h264"))
        return "video/h264";
    if (equal(ext, "hal"))
        return "application/vnd.hal+xml";
    if (equal(ext, "hbci"))
        return "application/vnd.hbci";
    if (equal(ext, "hbs"))
        return "text/x-handlebars-template charset=UTF-8";
    if (equal(ext, "hdd"))
        return "application/x-virtualbox-hdd";
    if (equal(ext, "hdf"))
        return "application/x-hdf";
    if (equal(ext, "heic"))
        return "image/heic";
    if (equal(ext, "heics"))
        return "image/heic-sequence";
    if (equal(ext, "heif"))
        return "image/heif";
    if (equal(ext, "heifs"))
        return "image/heif-sequence";
    if (equal(ext, "hej2"))
        return "image/hej2k";
    if (equal(ext, "held"))
        return "application/atsc-held+xml";
    if (equal(ext, "hh"))
        return "text/x-c charset=UTF-8";
    if (equal(ext, "hjson"))
        return "application/hjson";
    if (equal(ext, "hlp"))
        return "application/winhlp";
    if (equal(ext, "hpgl"))
        return "application/vnd.hp-hpgl";
    if (equal(ext, "hpid"))
        return "application/vnd.hp-hpid";
    if (equal(ext, "hps"))
        return "application/vnd.hp-hps";
    if (equal(ext, "hqx"))
        return "application/mac-binhex40";
    if (equal(ext, "htc"))
        return "text/x-component charset=UTF-8";
    if (equal(ext, "htke"))
        return "application/vnd.kenameaapp";
    if (equal(ext, "htm"))
        return "text/html charset=UTF-8";
    if (equal(ext, "html"))
        return "text/html charset=UTF-8";
    if (equal(ext, "hvd"))
        return "application/vnd.yamaha.hv-dic";
    if (equal(ext, "hvp"))
        return "application/vnd.yamaha.hv-voice";
    if (equal(ext, "hvs"))
        return "application/vnd.yamaha.hv-script";
    if (equal(ext, "i2g"))
        return "application/vnd.intergeo";
    if (equal(ext, "icc"))
        return "application/vnd.iccprofile";
    if (equal(ext, "ice"))
        return "x-conference/x-cooltalk";
    if (equal(ext, "icm"))
        return "application/vnd.iccprofile";
    if (equal(ext, "ico"))
        return "image/vnd.microsoft.icon";
    if (equal(ext, "ics"))
        return "text/calendar charset=UTF-8";
    if (equal(ext, "ief"))
        return "image/ief";
    if (equal(ext, "ifb"))
        return "text/calendar charset=UTF-8";
    if (equal(ext, "ifm"))
        return "application/vnd.shana.informed.formdata";
    if (equal(ext, "iges"))
        return "model/iges";
    if (equal(ext, "igl"))
        return "application/vnd.igloader";
    if (equal(ext, "igm"))
        return "application/vnd.insors.igm";
    if (equal(ext, "igs"))
        return "model/iges";
    if (equal(ext, "igx"))
        return "application/vnd.micrografx.igx";
    if (equal(ext, "iif"))
        return "application/vnd.shana.informed.interchange";
    if (equal(ext, "img"))
        return "application/octet-stream";
    if (equal(ext, "imp"))
        return "application/vnd.accpac.simply.imp";
    if (equal(ext, "ims"))
        return "application/vnd.ms-ims";
    if (equal(ext, "in"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "ini"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "ink"))
        return "application/inkml+xml";
    if (equal(ext, "inkml"))
        return "application/inkml+xml";
    if (equal(ext, "install"))
        return "application/x-install-instructions";
    if (equal(ext, "iota"))
        return "application/vnd.astraea-software.iota";
    if (equal(ext, "ipfix"))
        return "application/ipfix";
    if (equal(ext, "ipk"))
        return "application/vnd.shana.informed.package";
    if (equal(ext, "ipynb"))
        return "application/x-ipynb+json";
    if (equal(ext, "irm"))
        return "application/vnd.ibm.rights-management";
    if (equal(ext, "irp"))
        return "application/vnd.irepository.package+xml";
    if (equal(ext, "iso"))
        return "application/octet-stream";
    if (equal(ext, "itp"))
        return "application/vnd.shana.informed.formtemplate";
    if (equal(ext, "its"))
        return "application/its+xml";
    if (equal(ext, "ivp"))
        return "application/vnd.immervision-ivp";
    if (equal(ext, "ivu"))
        return "application/vnd.immervision-ivu";
    if (equal(ext, "jad"))
        return "text/vnd.sun.j2me.app-descriptor charset=UTF-8";
    if (equal(ext, "jade"))
        return "text/jade charset=UTF-8";
    if (equal(ext, "jaii"))
        return "image/jaii";
    if (equal(ext, "jais"))
        return "image/jais";
    if (equal(ext, "jam"))
        return "application/vnd.jam";
    if (equal(ext, "jar"))
        return "application/java-archive";
    if (equal(ext, "jardiff"))
        return "application/x-java-archive-diff";
    if (equal(ext, "java"))
        return "text/x-java-source charset=UTF-8";
    if (equal(ext, "jfif"))
        return "image/pjpeg";
    if (equal(ext, "jhc"))
        return "image/jphc";
    if (equal(ext, "jisp"))
        return "application/vnd.jisp";
    if (equal(ext, "jls"))
        return "image/jls";
    if (equal(ext, "jlt"))
        return "application/vnd.hp-jlyt";
    if (equal(ext, "jng"))
        return "image/x-jng";
    if (equal(ext, "jnlp"))
        return "application/x-java-jnlp-file";
    if (equal(ext, "joda"))
        return "application/vnd.joost.joda-archive";
    if (equal(ext, "jp2"))
        return "image/jp2";
    if (equal(ext, "jpe"))
        return "image/jpeg";
    if (equal(ext, "jpeg"))
        return "image/jpeg";
    if (equal(ext, "jpf"))
        return "image/jpx";
    if (equal(ext, "jpg"))
        return "image/jpeg";
    if (equal(ext, "jpg2"))
        return "image/jp2";
    if (equal(ext, "jpgm"))
        return "image/jpm";
    if (equal(ext, "jpgv"))
        return "video/jpeg";
    if (equal(ext, "jph"))
        return "image/jph";
    if (equal(ext, "jpm"))
        return "image/jpm";
    if (equal(ext, "jpx"))
        return "image/jpx";
    if (equal(ext, "js"))
        return "application/javascript";
    if (equal(ext, "json"))
        return "application/json";
    if (equal(ext, "json5"))
        return "application/json5";
    if (equal(ext, "jsonld"))
        return "application/ld+json";
    if (equal(ext, "jsonml"))
        return "application/jsonml+json";
    if (equal(ext, "jsx"))
        return "text/jsx charset=UTF-8";
    if (equal(ext, "jt"))
        return "model/jt";
    if (equal(ext, "jxl"))
        return "image/jxl";
    if (equal(ext, "jxr"))
        return "image/jxr";
    if (equal(ext, "jxra"))
        return "image/jxra";
    if (equal(ext, "jxrs"))
        return "image/jxrs";
    if (equal(ext, "jxs"))
        return "image/jxs";
    if (equal(ext, "jxsc"))
        return "image/jxsc";
    if (equal(ext, "jxsi"))
        return "image/jxsi";
    if (equal(ext, "jxss"))
        return "image/jxss";
    if (equal(ext, "kar"))
        return "audio/midi";
    if (equal(ext, "karbon"))
        return "application/vnd.kde.karbon";
    if (equal(ext, "kdbx"))
        return "application/x-keepass2";
    if (equal(ext, "key"))
        return "application/vnd.apple.keynote";
    if (equal(ext, "kfo"))
        return "application/vnd.kde.kformula";
    if (equal(ext, "kia"))
        return "application/vnd.kidspiration";
    if (equal(ext, "kml"))
        return "application/vnd.google-earth.kml+xml";
    if (equal(ext, "kmz"))
        return "application/vnd.google-earth.kmz";
    if (equal(ext, "kne"))
        return "application/vnd.kinar";
    if (equal(ext, "knp"))
        return "application/vnd.kinar";
    if (equal(ext, "kon"))
        return "application/vnd.kde.kontour";
    if (equal(ext, "kpr"))
        return "application/vnd.kde.kpresenter";
    if (equal(ext, "kpt"))
        return "application/vnd.kde.kpresenter";
    if (equal(ext, "kpxx"))
        return "application/vnd.ds-keypoint";
    if (equal(ext, "ksp"))
        return "application/vnd.kde.kspread";
    if (equal(ext, "ktr"))
        return "application/vnd.kahootz";
    if (equal(ext, "ktx"))
        return "image/ktx";
    if (equal(ext, "ktx2"))
        return "image/ktx2";
    if (equal(ext, "ktz"))
        return "application/vnd.kahootz";
    if (equal(ext, "kwd"))
        return "application/vnd.kde.kword";
    if (equal(ext, "kwt"))
        return "application/vnd.kde.kword";
    if (equal(ext, "lasxml"))
        return "application/vnd.las.las+xml";
    if (equal(ext, "latex"))
        return "application/x-latex";
    if (equal(ext, "lbd"))
        return "application/vnd.llamagraphics.life-balance.desktop";
    if (equal(ext, "lbe"))
        return "application/vnd.llamagraphics.life-balance.exchange+xml";
    if (equal(ext, "les"))
        return "application/vnd.hhe.lesson-player";
    if (equal(ext, "less"))
        return "text/less charset=UTF-8";
    if (equal(ext, "lgr"))
        return "application/lgr+xml";
    if (equal(ext, "lha"))
        return "application/x-lzh-compressed";
    if (equal(ext, "link66"))
        return "application/vnd.route66.link66+xml";
    if (equal(ext, "list"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "list3820"))
        return "application/vnd.ibm.modcap";
    if (equal(ext, "listafp"))
        return "application/vnd.ibm.modcap";
    if (equal(ext, "litcoffee"))
        return "text/coffeescript charset=UTF-8";
    if (equal(ext, "lnk"))
        return "application/x-ms-shortcut";
    if (equal(ext, "log"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "lostxml"))
        return "application/lost+xml";
    if (equal(ext, "lottie"))
        return "application/zip+dotlottie";
    if (equal(ext, "lrf"))
        return "application/octet-stream";
    if (equal(ext, "lrm"))
        return "application/vnd.ms-lrm";
    if (equal(ext, "ltf"))
        return "application/vnd.frogans.ltf";
    if (equal(ext, "lua"))
        return "text/x-lua charset=UTF-8";
    if (equal(ext, "luac"))
        return "application/x-lua-bytecode";
    if (equal(ext, "lvp"))
        return "audio/vnd.lucent.voice";
    if (equal(ext, "lwp"))
        return "application/vnd.lotus-wordpro";
    if (equal(ext, "lzh"))
        return "application/x-lzh-compressed";
    if (equal(ext, "m13"))
        return "application/x-msmediaview";
    if (equal(ext, "m14"))
        return "application/x-msmediaview";
    if (equal(ext, "m1v"))
        return "video/mpeg";
    if (equal(ext, "m21"))
        return "application/mp21";
    if (equal(ext, "m2a"))
        return "audio/mpeg";
    if (equal(ext, "m2t"))
        return "video/mp2t";
    if (equal(ext, "m2ts"))
        return "video/mp2t";
    if (equal(ext, "m2v"))
        return "video/mpeg";
    if (equal(ext, "m3a"))
        return "audio/mpeg";
    if (equal(ext, "m3u"))
        return "audio/x-mpegurl";
    if (equal(ext, "m3u8"))
        return "application/vnd.apple.mpegurl";
    if (equal(ext, "m4a"))
        return "audio/mp4";
    if (equal(ext, "m4b"))
        return "audio/mp4";
    if (equal(ext, "m4p"))
        return "application/mp4";
    if (equal(ext, "m4s"))
        return "video/iso.segment";
    if (equal(ext, "m4u"))
        return "video/vnd.mpegurl";
    if (equal(ext, "m4v"))
        return "video/x-m4v";
    if (equal(ext, "ma"))
        return "application/mathematica";
    if (equal(ext, "mads"))
        return "application/mads+xml";
    if (equal(ext, "maei"))
        return "application/mmt-aei+xml";
    if (equal(ext, "mag"))
        return "application/vnd.ecowin.chart";
    if (equal(ext, "maker"))
        return "application/vnd.framemaker";
    if (equal(ext, "man"))
        return "text/troff charset=UTF-8";
    if (equal(ext, "manifest"))
        return "text/cache-manifest charset=UTF-8";
    if (equal(ext, "map"))
        return "application/json";
    if (equal(ext, "mar"))
        return "application/octet-stream";
    if (equal(ext, "markdown"))
        return "text/markdown charset=UTF-8";
    if (equal(ext, "mathml"))
        return "application/mathml+xml";
    if (equal(ext, "mb"))
        return "application/mathematica";
    if (equal(ext, "mbk"))
        return "application/vnd.mobius.mbk";
    if (equal(ext, "mbox"))
        return "application/mbox";
    if (equal(ext, "mc1"))
        return "application/vnd.medcalcdata";
    if (equal(ext, "mcd"))
        return "application/vnd.mcd";
    if (equal(ext, "mcurl"))
        return "text/vnd.curl.mcurl charset=UTF-8";
    if (equal(ext, "md"))
        return "text/markdown charset=UTF-8";
    if (equal(ext, "mdb"))
        return "application/x-msaccess";
    if (equal(ext, "mdi"))
        return "image/vnd.ms-modi";
    if (equal(ext, "mdx"))
        return "text/mdx charset=UTF-8";
    if (equal(ext, "me"))
        return "text/troff charset=UTF-8";
    if (equal(ext, "mesh"))
        return "model/mesh";
    if (equal(ext, "meta4"))
        return "application/metalink4+xml";
    if (equal(ext, "metalink"))
        return "application/metalink+xml";
    if (equal(ext, "mets"))
        return "application/mets+xml";
    if (equal(ext, "mfm"))
        return "application/vnd.mfmp";
    if (equal(ext, "mft"))
        return "application/rpki-manifest";
    if (equal(ext, "mgp"))
        return "application/vnd.osgeo.mapguide.package";
    if (equal(ext, "mgz"))
        return "application/vnd.proteus.magazine";
    if (equal(ext, "mht"))
        return "message/rfc822";
    if (equal(ext, "mhtml"))
        return "message/rfc822";
    if (equal(ext, "mid"))
        return "audio/midi";
    if (equal(ext, "midi"))
        return "audio/midi";
    if (equal(ext, "mie"))
        return "application/x-mie";
    if (equal(ext, "mif"))
        return "application/vnd.mif";
    if (equal(ext, "mime"))
        return "message/rfc822";
    if (equal(ext, "mj2"))
        return "video/mj2";
    if (equal(ext, "mjp2"))
        return "video/mj2";
    if (equal(ext, "mjs"))
        return "text/javascript charset=UTF-8";
    if (equal(ext, "mk3d"))
        return "video/x-matroska";
    if (equal(ext, "mka"))
        return "audio/x-matroska";
    if (equal(ext, "mkd"))
        return "text/x-markdown charset=UTF-8";
    if (equal(ext, "mks"))
        return "video/x-matroska";
    if (equal(ext, "mkv"))
        return "video/x-matroska";
    if (equal(ext, "mlp"))
        return "application/vnd.dolby.mlp";
    if (equal(ext, "mmd"))
        return "application/vnd.chipnuts.karaoke-mmd";
    if (equal(ext, "mmf"))
        return "application/vnd.smaf";
    if (equal(ext, "mml"))
        return "text/mathml charset=UTF-8";
    if (equal(ext, "mmr"))
        return "image/vnd.fujixerox.edmics-mmr";
    if (equal(ext, "mng"))
        return "video/x-mng";
    if (equal(ext, "mny"))
        return "application/x-msmoney";
    if (equal(ext, "mobi"))
        return "application/x-mobipocket-ebook";
    if (equal(ext, "mods"))
        return "application/mods+xml";
    if (equal(ext, "mov"))
        return "video/quicktime";
    if (equal(ext, "movie"))
        return "video/x-sgi-movie";
    if (equal(ext, "mp2"))
        return "audio/mpeg";
    if (equal(ext, "mp21"))
        return "application/mp21";
    if (equal(ext, "mp2a"))
        return "audio/mpeg";
    if (equal(ext, "mp3"))
        return "audio/mp3";
    if (equal(ext, "mp4"))
        return "video/mp4";
    if (equal(ext, "mp4a"))
        return "audio/mp4";
    if (equal(ext, "mp4s"))
        return "application/mp4";
    if (equal(ext, "mp4v"))
        return "video/mp4";
    if (equal(ext, "mpc"))
        return "application/vnd.mophun.certificate";
    if (equal(ext, "mpd"))
        return "application/dash+xml";
    if (equal(ext, "mpe"))
        return "video/mpeg";
    if (equal(ext, "mpeg"))
        return "video/mpeg";
    if (equal(ext, "mpf"))
        return "application/media-policy-dataset+xml";
    if (equal(ext, "mpg"))
        return "video/mpeg";
    if (equal(ext, "mpg4"))
        return "application/mp4";
    if (equal(ext, "mpga"))
        return "audio/mpeg";
    if (equal(ext, "mpkg"))
        return "application/vnd.apple.installer+xml";
    if (equal(ext, "mpm"))
        return "application/vnd.blueice.multipass";
    if (equal(ext, "mpn"))
        return "application/vnd.mophun.application";
    if (equal(ext, "mpp"))
        return "application/dash-patch+xml";
    if (equal(ext, "mpt"))
        return "application/vnd.ms-project";
    if (equal(ext, "mpy"))
        return "application/vnd.ibm.minipay";
    if (equal(ext, "mqy"))
        return "application/vnd.mobius.mqy";
    if (equal(ext, "mrc"))
        return "application/marc";
    if (equal(ext, "mrcx"))
        return "application/marcxml+xml";
    if (equal(ext, "ms"))
        return "text/troff charset=UTF-8";
    if (equal(ext, "mscml"))
        return "application/mediaservercontrol+xml";
    if (equal(ext, "mseed"))
        return "application/vnd.fdsn.mseed";
    if (equal(ext, "mseq"))
        return "application/vnd.mseq";
    if (equal(ext, "msf"))
        return "application/vnd.epson.msf";
    if (equal(ext, "msg"))
        return "application/vnd.ms-outlook";
    if (equal(ext, "msh"))
        return "model/mesh";
    if (equal(ext, "msi"))
        return "application/octet-stream";
    if (equal(ext, "msix"))
        return "application/msix";
    if (equal(ext, "msixbundle"))
        return "application/msixbundle";
    if (equal(ext, "msl"))
        return "application/vnd.mobius.msl";
    if (equal(ext, "msm"))
        return "application/octet-stream";
    if (equal(ext, "msp"))
        return "application/octet-stream";
    if (equal(ext, "msty"))
        return "application/vnd.muvee.style";
    if (equal(ext, "mtl"))
        return "model/mtl";
    if (equal(ext, "mts"))
        return "model/vnd.mts";
    if (equal(ext, "mus"))
        return "application/vnd.musician";
    if (equal(ext, "musd"))
        return "application/mmt-usd+xml";
    if (equal(ext, "musicxml"))
        return "application/vnd.recordare.musicxml+xml";
    if (equal(ext, "mvb"))
        return "application/x-msmediaview";
    if (equal(ext, "mvt"))
        return "application/vnd.mapbox-vector-tile";
    if (equal(ext, "mwf"))
        return "application/vnd.mfer";
    if (equal(ext, "mxf"))
        return "application/mxf";
    if (equal(ext, "mxl"))
        return "application/vnd.recordare.musicxml";
    if (equal(ext, "mxmf"))
        return "audio/mobile-xmf";
    if (equal(ext, "mxml"))
        return "application/xv+xml";
    if (equal(ext, "mxs"))
        return "application/vnd.triscape.mxs";
    if (equal(ext, "mxu"))
        return "video/vnd.mpegurl";
    if (equal(ext, "n-gage"))
        return "application/vnd.nokia.n-gage.symbian.install";
    if (equal(ext, "n3"))
        return "text/n3 charset=UTF-8";
    if (equal(ext, "nb"))
        return "application/mathematica";
    if (equal(ext, "nbp"))
        return "application/vnd.wolfram.player";
    if (equal(ext, "nc"))
        return "application/x-netcdf";
    if (equal(ext, "ncx"))
        return "application/x-dtbncx+xml";
    if (equal(ext, "nfo"))
        return "text/x-nfo charset=UTF-8";
    if (equal(ext, "ngdat"))
        return "application/vnd.nokia.n-gage.data";
    if (equal(ext, "nitf"))
        return "application/vnd.nitf";
    if (equal(ext, "nlu"))
        return "application/vnd.neurolanguage.nlu";
    if (equal(ext, "nml"))
        return "application/vnd.enliven";
    if (equal(ext, "nnd"))
        return "application/vnd.noblenet-directory";
    if (equal(ext, "nns"))
        return "application/vnd.noblenet-sealer";
    if (equal(ext, "nnw"))
        return "application/vnd.noblenet-web";
    if (equal(ext, "npx"))
        return "image/vnd.net-fpx";
    if (equal(ext, "nq"))
        return "application/n-quads";
    if (equal(ext, "nsc"))
        return "application/x-conference";
    if (equal(ext, "nsf"))
        return "application/vnd.lotus-notes";
    if (equal(ext, "nt"))
        return "application/n-triples";
    if (equal(ext, "ntf"))
        return "application/vnd.nitf";
    if (equal(ext, "numbers"))
        return "application/vnd.apple.numbers";
    if (equal(ext, "nzb"))
        return "application/x-nzb";
    if (equal(ext, "oa2"))
        return "application/vnd.fujitsu.oasys2";
    if (equal(ext, "oa3"))
        return "application/vnd.fujitsu.oasys3";
    if (equal(ext, "oas"))
        return "application/vnd.fujitsu.oasys";
    if (equal(ext, "obd"))
        return "application/x-msbinder";
    if (equal(ext, "obgx"))
        return "application/vnd.openblox.game+xml";
    if (equal(ext, "obj"))
        return "application/x-tgif";
    if (equal(ext, "oda"))
        return "application/oda";
    if (equal(ext, "odb"))
        return "application/vnd.oasis.opendocument.database";
    if (equal(ext, "odc"))
        return "application/vnd.oasis.opendocument.chart";
    if (equal(ext, "odf"))
        return "application/vnd.oasis.opendocument.formula";
    if (equal(ext, "odft"))
        return "application/vnd.oasis.opendocument.formula-template";
    if (equal(ext, "odg"))
        return "application/vnd.oasis.opendocument.graphics";
    if (equal(ext, "odi"))
        return "application/vnd.oasis.opendocument.image";
    if (equal(ext, "odm"))
        return "application/vnd.oasis.opendocument.text-master";
    if (equal(ext, "odp"))
        return "application/vnd.oasis.opendocument.presentation";
    if (equal(ext, "ods"))
        return "application/vnd.oasis.opendocument.spreadsheet";
    if (equal(ext, "odt"))
        return "application/vnd.oasis.opendocument.text";
    if (equal(ext, "oga"))
        return "audio/ogg";
    if (equal(ext, "ogex"))
        return "model/vnd.opengex";
    if (equal(ext, "ogg"))
        return "audio/ogg";
    if (equal(ext, "ogv"))
        return "video/ogg";
    if (equal(ext, "ogx"))
        return "application/ogg";
    if (equal(ext, "omdoc"))
        return "application/omdoc+xml";
    if (equal(ext, "one"))
        return "application/onenote";
    if (equal(ext, "onea"))
        return "application/onenote";
    if (equal(ext, "onepkg"))
        return "application/onenote";
    if (equal(ext, "onetmp"))
        return "application/onenote";
    if (equal(ext, "onetoc"))
        return "application/onenote";
    if (equal(ext, "onetoc2"))
        return "application/onenote";
    if (equal(ext, "opf"))
        return "application/oebps-package+xml";
    if (equal(ext, "opml"))
        return "text/x-opml charset=UTF-8";
    if (equal(ext, "oprc"))
        return "application/vnd.palm";
    if (equal(ext, "opus"))
        return "audio/ogg";
    if (equal(ext, "org"))
        return "application/vnd.lotus-organizer";
    if (equal(ext, "osf"))
        return "application/vnd.yamaha.openscoreformat";
    if (equal(ext, "osfpvg"))
        return "application/vnd.yamaha.openscoreformat.osfpvg+xml";
    if (equal(ext, "osm"))
        return "application/vnd.openstreetmap.data+xml";
    if (equal(ext, "otc"))
        return "application/vnd.oasis.opendocument.chart-template";
    if (equal(ext, "otf"))
        return "font/otf";
    if (equal(ext, "otg"))
        return "application/vnd.oasis.opendocument.graphics-template";
    if (equal(ext, "oth"))
        return "application/vnd.oasis.opendocument.text-web";
    if (equal(ext, "oti"))
        return "application/vnd.oasis.opendocument.image-template";
    if (equal(ext, "otp"))
        return "application/vnd.oasis.opendocument.presentation-template";
    if (equal(ext, "ots"))
        return "application/vnd.oasis.opendocument.spreadsheet-template";
    if (equal(ext, "ott"))
        return "application/vnd.oasis.opendocument.text-template";
    if (equal(ext, "ova"))
        return "application/x-virtualbox-ova";
    if (equal(ext, "ovf"))
        return "application/x-virtualbox-ovf";
    if (equal(ext, "owl"))
        return "application/rdf+xml";
    if (equal(ext, "oxps"))
        return "application/oxps";
    if (equal(ext, "oxt"))
        return "application/vnd.openofficeorg.extension";
    if (equal(ext, "p"))
        return "text/x-pascal charset=UTF-8";
    if (equal(ext, "p10"))
        return "application/pkcs10";
    if (equal(ext, "p12"))
        return "application/x-pkcs12";
    if (equal(ext, "p21"))
        return "model/step";
    if (equal(ext, "p7b"))
        return "application/x-pkcs7-certificates";
    if (equal(ext, "p7c"))
        return "application/pkcs7-mime";
    if (equal(ext, "p7m"))
        return "application/pkcs7-mime";
    if (equal(ext, "p7r"))
        return "application/x-pkcs7-certreqresp";
    if (equal(ext, "p7s"))
        return "application/pkcs7-signature";
    if (equal(ext, "p8"))
        return "application/pkcs8";
    if (equal(ext, "pac"))
        return "application/x-ns-proxy-autoconfig";
    if (equal(ext, "pages"))
        return "application/vnd.apple.pages";
    if (equal(ext, "pas"))
        return "text/x-pascal charset=UTF-8";
    if (equal(ext, "paw"))
        return "application/vnd.pawaafile";
    if (equal(ext, "pbd"))
        return "application/vnd.powerbuilder6";
    if (equal(ext, "pbm"))
        return "image/x-portable-bitmap";
    if (equal(ext, "pcap"))
        return "application/vnd.tcpdump.pcap";
    if (equal(ext, "pcf"))
        return "application/x-font-pcf";
    if (equal(ext, "pcl"))
        return "application/vnd.hp-pcl";
    if (equal(ext, "pclxl"))
        return "application/vnd.hp-pclxl";
    if (equal(ext, "pct"))
        return "image/x-pict";
    if (equal(ext, "pcurl"))
        return "application/vnd.curl.pcurl";
    if (equal(ext, "pcx"))
        return "image/vnd.zbrush.pcx";
    if (equal(ext, "pdb"))
        return "application/vnd.palm";
    if (equal(ext, "pde"))
        return "text/x-processing charset=UTF-8";
    if (equal(ext, "pdf"))
        return "application/pdf";
    if (equal(ext, "pem"))
        return "application/x-x509-ca-cert";
    if (equal(ext, "pfa"))
        return "application/x-font-type1";
    if (equal(ext, "pfb"))
        return "application/x-font-type1";
    if (equal(ext, "pfm"))
        return "application/x-font-type1";
    if (equal(ext, "pfr"))
        return "application/font-tdpfr";
    if (equal(ext, "pfx"))
        return "application/x-pkcs12";
    if (equal(ext, "pgm"))
        return "image/x-portable-graymap";
    if (equal(ext, "pgn"))
        return "application/x-chess-pgn";
    if (equal(ext, "pgp"))
        return "application/pgp-encrypted";
    if (equal(ext, "php"))
        return "application/x-httpd-php";
    if (equal(ext, "pic"))
        return "image/x-pict";
    if (equal(ext, "pkg"))
        return "application/octet-stream";
    if (equal(ext, "pki"))
        return "application/pkixcmp";
    if (equal(ext, "pkipath"))
        return "application/pkix-pkipath";
    if (equal(ext, "pkpass"))
        return "application/vnd.apple.pkpass";
    if (equal(ext, "pl"))
        return "application/x-perl";
    if (equal(ext, "plb"))
        return "application/vnd.3gpp.pic-bw-large";
    if (equal(ext, "plc"))
        return "application/vnd.mobius.plc";
    if (equal(ext, "plf"))
        return "application/vnd.pocketlearn";
    if (equal(ext, "pls"))
        return "application/pls+xml";
    if (equal(ext, "pm"))
        return "application/x-perl";
    if (equal(ext, "pml"))
        return "application/vnd.ctc-posml";
    if (equal(ext, "png"))
        return "image/png";
    if (equal(ext, "pnm"))
        return "image/x-portable-anymap";
    if (equal(ext, "portpkg"))
        return "application/vnd.macports.portpkg";
    if (equal(ext, "pot"))
        return "application/vnd.ms-powerpoint";
    if (equal(ext, "potm"))
        return "application/vnd.ms-powerpoint.template.macroenabled.12";
    if (equal(ext, "potx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.template";
    if (equal(ext, "ppam"))
        return "application/vnd.ms-powerpoint.addin.macroenabled.12";
    if (equal(ext, "ppd"))
        return "application/vnd.cups-ppd";
    if (equal(ext, "ppm"))
        return "image/x-portable-pixmap";
    if (equal(ext, "pps"))
        return "application/vnd.ms-powerpoint";
    if (equal(ext, "ppsm"))
        return "application/vnd.ms-powerpoint.slideshow.macroenabled.12";
    if (equal(ext, "ppsx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.slideshow";
    if (equal(ext, "ppt"))
        return "application/vnd.ms-powerpoint";
    if (equal(ext, "pptm"))
        return "application/vnd.ms-powerpoint.presentation.macroenabled.12";
    if (equal(ext, "pptx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.presentation";
    if (equal(ext, "pqa"))
        return "application/vnd.palm";
    if (equal(ext, "prc"))
        return "application/x-mobipocket-ebook";
    if (equal(ext, "pre"))
        return "application/vnd.lotus-freelance";
    if (equal(ext, "prf"))
        return "application/pics-rules";
    if (equal(ext, "provx"))
        return "application/provenance+xml";
    if (equal(ext, "ps"))
        return "application/postscript";
    if (equal(ext, "psb"))
        return "application/vnd.3gpp.pic-bw-small";
    if (equal(ext, "psd"))
        return "image/vnd.adobe.photoshop";
    if (equal(ext, "psf"))
        return "application/x-font-linux-psf";
    if (equal(ext, "pskcxml"))
        return "application/pskc+xml";
    if (equal(ext, "pti"))
        return "image/prs.pti";
    if (equal(ext, "ptid"))
        return "application/vnd.pvi.ptid1";
    if (equal(ext, "pub"))
        return "application/x-mspublisher";
    if (equal(ext, "pvb"))
        return "application/vnd.3gpp.pic-bw-var";
    if (equal(ext, "pwn"))
        return "application/vnd.3m.post-it-notes";
    if (equal(ext, "pya"))
        return "audio/vnd.ms-playready.media.pya";
    if (equal(ext, "pyo"))
        return "model/vnd.pytha.pyox";
    if (equal(ext, "pyox"))
        return "model/vnd.pytha.pyox";
    if (equal(ext, "pyv"))
        return "video/vnd.ms-playready.media.pyv";
    if (equal(ext, "qam"))
        return "application/vnd.epson.quickanime";
    if (equal(ext, "qbo"))
        return "application/vnd.intu.qbo";
    if (equal(ext, "qfx"))
        return "application/vnd.intu.qfx";
    if (equal(ext, "qps"))
        return "application/vnd.publishare-delta-tree";
    if (equal(ext, "qt"))
        return "video/quicktime";
    if (equal(ext, "qwd"))
        return "application/vnd.quark.quarkxpress";
    if (equal(ext, "qwt"))
        return "application/vnd.quark.quarkxpress";
    if (equal(ext, "qxb"))
        return "application/vnd.quark.quarkxpress";
    if (equal(ext, "qxd"))
        return "application/vnd.quark.quarkxpress";
    if (equal(ext, "qxl"))
        return "application/vnd.quark.quarkxpress";
    if (equal(ext, "qxt"))
        return "application/vnd.quark.quarkxpress";
    if (equal(ext, "ra"))
        return "audio/x-pn-realaudio";
    if (equal(ext, "ram"))
        return "audio/x-pn-realaudio";
    if (equal(ext, "raml"))
        return "application/raml+yaml";
    if (equal(ext, "rapd"))
        return "application/route-apd+xml";
    if (equal(ext, "rar"))
        return "application/vnd.rar";
    if (equal(ext, "ras"))
        return "image/x-cmu-raster";
    if (equal(ext, "rcprofile"))
        return "application/vnd.ipunplugged.rcprofile";
    if (equal(ext, "rdf"))
        return "application/rdf+xml";
    if (equal(ext, "rdz"))
        return "application/vnd.data-vision.rdz";
    if (equal(ext, "relo"))
        return "application/p2p-overlay+xml";
    if (equal(ext, "rep"))
        return "application/vnd.businessobjects";
    if (equal(ext, "res"))
        return "application/x-dtbresource+xml";
    if (equal(ext, "rgb"))
        return "image/x-rgb";
    if (equal(ext, "rif"))
        return "application/reginfo+xml";
    if (equal(ext, "rip"))
        return "audio/vnd.rip";
    if (equal(ext, "ris"))
        return "application/x-research-info-systems";
    if (equal(ext, "rl"))
        return "application/resource-lists+xml";
    if (equal(ext, "rlc"))
        return "image/vnd.fujixerox.edmics-rlc";
    if (equal(ext, "rld"))
        return "application/resource-lists-diff+xml";
    if (equal(ext, "rm"))
        return "application/vnd.rn-realmedia";
    if (equal(ext, "rmi"))
        return "audio/midi";
    if (equal(ext, "rmp"))
        return "audio/x-pn-realaudio-plugin";
    if (equal(ext, "rms"))
        return "application/vnd.jcp.javame.midlet-rms";
    if (equal(ext, "rmvb"))
        return "application/vnd.rn-realmedia-vbr";
    if (equal(ext, "rnc"))
        return "application/relax-ng-compact-syntax";
    if (equal(ext, "rng"))
        return "application/xml";
    if (equal(ext, "roa"))
        return "application/rpki-roa";
    if (equal(ext, "roff"))
        return "text/troff charset=UTF-8";
    if (equal(ext, "rp9"))
        return "application/vnd.cloanto.rp9";
    if (equal(ext, "rpm"))
        return "application/x-redhat-package-manager";
    if (equal(ext, "rpss"))
        return "application/vnd.nokia.radio-presets";
    if (equal(ext, "rpst"))
        return "application/vnd.nokia.radio-preset";
    if (equal(ext, "rq"))
        return "application/sparql-query";
    if (equal(ext, "rs"))
        return "application/rls-services+xml";
    if (equal(ext, "rsat"))
        return "application/atsc-rsat+xml";
    if (equal(ext, "rsd"))
        return "application/rsd+xml";
    if (equal(ext, "rsheet"))
        return "application/urc-ressheet+xml";
    if (equal(ext, "rss"))
        return "application/rss+xml";
    if (equal(ext, "rtf"))
        return "application/rtf";
    if (equal(ext, "rtx"))
        return "text/richtext charset=UTF-8";
    if (equal(ext, "run"))
        return "application/x-makeself";
    if (equal(ext, "rusd"))
        return "application/route-usd+xml";
    if (equal(ext, "s"))
        return "text/x-asm charset=UTF-8";
    if (equal(ext, "s3m"))
        return "audio/s3m";
    if (equal(ext, "saf"))
        return "application/vnd.yamaha.smaf-audio";
    if (equal(ext, "sass"))
        return "text/x-sass charset=UTF-8";
    if (equal(ext, "sbml"))
        return "application/sbml+xml";
    if (equal(ext, "sc"))
        return "application/vnd.ibm.secure-container";
    if (equal(ext, "scd"))
        return "application/x-msschedule";
    if (equal(ext, "scm"))
        return "application/vnd.lotus-screencam";
    if (equal(ext, "scq"))
        return "application/scvp-cv-request";
    if (equal(ext, "scs"))
        return "application/scvp-cv-response";
    if (equal(ext, "scss"))
        return "text/x-scss charset=UTF-8";
    if (equal(ext, "scurl"))
        return "text/vnd.curl.scurl charset=UTF-8";
    if (equal(ext, "sda"))
        return "application/vnd.stardivision.draw";
    if (equal(ext, "sdc"))
        return "application/vnd.stardivision.calc";
    if (equal(ext, "sdd"))
        return "application/vnd.stardivision.impress";
    if (equal(ext, "sdkd"))
        return "application/vnd.solent.sdkm+xml";
    if (equal(ext, "sdkm"))
        return "application/vnd.solent.sdkm+xml";
    if (equal(ext, "sdp"))
        return "application/sdp";
    if (equal(ext, "sdw"))
        return "application/vnd.stardivision.writer";
    if (equal(ext, "sea"))
        return "application/x-sea";
    if (equal(ext, "see"))
        return "application/vnd.seemail";
    if (equal(ext, "seed"))
        return "application/vnd.fdsn.seed";
    if (equal(ext, "sema"))
        return "application/vnd.sema";
    if (equal(ext, "semd"))
        return "application/vnd.semd";
    if (equal(ext, "semf"))
        return "application/vnd.semf";
    if (equal(ext, "senmlx"))
        return "application/senml+xml";
    if (equal(ext, "sensmlx"))
        return "application/sensml+xml";
    if (equal(ext, "ser"))
        return "application/java-serialized-object";
    if (equal(ext, "setpay"))
        return "application/set-payment-initiation";
    if (equal(ext, "setreg"))
        return "application/set-registration-initiation";
    if (equal(ext, "sfd-hdstx"))
        return "application/vnd.hydrostatix.sof-data";
    if (equal(ext, "sfs"))
        return "application/vnd.spotfire.sfs";
    if (equal(ext, "sfv"))
        return "text/x-sfv charset=UTF-8";
    if (equal(ext, "sgi"))
        return "image/sgi";
    if (equal(ext, "sgl"))
        return "application/vnd.stardivision.writer-global";
    if (equal(ext, "sgm"))
        return "text/sgml charset=UTF-8";
    if (equal(ext, "sgml"))
        return "text/sgml charset=UTF-8";
    if (equal(ext, "sh"))
        return "application/x-sh";
    if (equal(ext, "shar"))
        return "application/x-shar";
    if (equal(ext, "shex"))
        return "text/shex charset=UTF-8";
    if (equal(ext, "shf"))
        return "application/shf+xml";
    if (equal(ext, "shtml"))
        return "text/html charset=UTF-8";
    if (equal(ext, "sid"))
        return "image/x-mrsid-image";
    if (equal(ext, "sieve"))
        return "application/sieve";
    if (equal(ext, "sig"))
        return "application/pgp-signature";
    if (equal(ext, "sil"))
        return "audio/silk";
    if (equal(ext, "silo"))
        return "model/mesh";
    if (equal(ext, "sis"))
        return "application/vnd.symbian.install";
    if (equal(ext, "sisx"))
        return "application/vnd.symbian.install";
    if (equal(ext, "sit"))
        return "application/x-stuffit";
    if (equal(ext, "sitx"))
        return "application/x-stuffitx";
    if (equal(ext, "siv"))
        return "application/sieve";
    if (equal(ext, "skd"))
        return "application/vnd.koan";
    if (equal(ext, "skm"))
        return "application/vnd.koan";
    if (equal(ext, "skp"))
        return "application/vnd.koan";
    if (equal(ext, "skt"))
        return "application/vnd.koan";
    if (equal(ext, "sldm"))
        return "application/vnd.ms-powerpoint.slide.macroenabled.12";
    if (equal(ext, "sldx"))
        return "application/vnd.openxmlformats-officedocument.presentationml.slide";
    if (equal(ext, "slim"))
        return "text/slim charset=UTF-8";
    if (equal(ext, "slm"))
        return "text/slim charset=UTF-8";
    if (equal(ext, "sls"))
        return "application/route-s-tsid+xml";
    if (equal(ext, "slt"))
        return "application/vnd.epson.salt";
    if (equal(ext, "sm"))
        return "application/vnd.stepmania.stepchart";
    if (equal(ext, "smf"))
        return "application/vnd.stardivision.math";
    if (equal(ext, "smi"))
        return "application/smil+xml";
    if (equal(ext, "smil"))
        return "application/smil+xml";
    if (equal(ext, "smv"))
        return "video/x-smv";
    if (equal(ext, "smzip"))
        return "application/vnd.stepmania.package";
    if (equal(ext, "snd"))
        return "audio/basic";
    if (equal(ext, "snf"))
        return "application/x-font-snf";
    if (equal(ext, "so"))
        return "application/octet-stream";
    if (equal(ext, "spc"))
        return "application/x-pkcs7-certificates";
    if (equal(ext, "spdx"))
        return "text/spdx charset=UTF-8";
    if (equal(ext, "spf"))
        return "application/vnd.yamaha.smaf-phrase";
    if (equal(ext, "spl"))
        return "application/x-futuresplash";
    if (equal(ext, "spot"))
        return "text/vnd.in3d.spot charset=UTF-8";
    if (equal(ext, "spp"))
        return "application/scvp-vp-response";
    if (equal(ext, "spq"))
        return "application/scvp-vp-request";
    if (equal(ext, "spx"))
        return "audio/ogg";
    if (equal(ext, "sql"))
        return "application/sql";
    if (equal(ext, "src"))
        return "application/x-wais-source";
    if (equal(ext, "srt"))
        return "application/x-subrip";
    if (equal(ext, "sru"))
        return "application/sru+xml";
    if (equal(ext, "srx"))
        return "application/sparql-results+xml";
    if (equal(ext, "ssdl"))
        return "application/ssdl+xml";
    if (equal(ext, "sse"))
        return "application/vnd.kodak-descriptor";
    if (equal(ext, "ssf"))
        return "application/vnd.epson.ssf";
    if (equal(ext, "ssml"))
        return "application/ssml+xml";
    if (equal(ext, "st"))
        return "application/vnd.sailingtracker.track";
    if (equal(ext, "stc"))
        return "application/vnd.sun.xml.calc.template";
    if (equal(ext, "std"))
        return "application/vnd.sun.xml.draw.template";
    if (equal(ext, "step"))
        return "model/step";
    if (equal(ext, "stf"))
        return "application/vnd.wt.stf";
    if (equal(ext, "sti"))
        return "application/vnd.sun.xml.impress.template";
    if (equal(ext, "stk"))
        return "application/hyperstudio";
    if (equal(ext, "stl"))
        return "application/vnd.ms-pki.stl";
    if (equal(ext, "stp"))
        return "model/step";
    if (equal(ext, "stpnc"))
        return "model/step";
    if (equal(ext, "stpx"))
        return "model/step+xml";
    if (equal(ext, "stpxz"))
        return "model/step-xml+zip";
    if (equal(ext, "stpz"))
        return "model/step+zip";
    if (equal(ext, "str"))
        return "application/vnd.pg.format";
    if (equal(ext, "stw"))
        return "application/vnd.sun.xml.writer.template";
    if (equal(ext, "styl"))
        return "text/stylus charset=UTF-8";
    if (equal(ext, "stylus"))
        return "text/stylus charset=UTF-8";
    if (equal(ext, "sub"))
        return "image/vnd.dvb.subtitle";
    if (equal(ext, "sus"))
        return "application/vnd.sus-calendar";
    if (equal(ext, "susp"))
        return "application/vnd.sus-calendar";
    if (equal(ext, "sv4cpio"))
        return "application/x-sv4cpio";
    if (equal(ext, "sv4crc"))
        return "application/x-sv4crc";
    if (equal(ext, "svc"))
        return "application/vnd.dvb.service";
    if (equal(ext, "svd"))
        return "application/vnd.svd";
    if (equal(ext, "svg"))
        return "image/svg+xml";
    if (equal(ext, "svgz"))
        return "image/svg+xml";
    if (equal(ext, "swa"))
        return "application/x-director";
    if (equal(ext, "swf"))
        return "application/x-shockwave-flash";
    if (equal(ext, "swi"))
        return "application/vnd.aristanetworks.swi";
    if (equal(ext, "swidtag"))
        return "application/swid+xml";
    if (equal(ext, "sxc"))
        return "application/vnd.sun.xml.calc";
    if (equal(ext, "sxd"))
        return "application/vnd.sun.xml.draw";
    if (equal(ext, "sxg"))
        return "application/vnd.sun.xml.writer.global";
    if (equal(ext, "sxi"))
        return "application/vnd.sun.xml.impress";
    if (equal(ext, "sxm"))
        return "application/vnd.sun.xml.math";
    if (equal(ext, "sxw"))
        return "application/vnd.sun.xml.writer";
    if (equal(ext, "t"))
        return "text/troff charset=UTF-8";
    if (equal(ext, "t3"))
        return "application/x-t3vm-image";
    if (equal(ext, "t38"))
        return "image/t38";
    if (equal(ext, "taglet"))
        return "application/vnd.mynfc";
    if (equal(ext, "tao"))
        return "application/vnd.tao.intent-module-archive";
    if (equal(ext, "tap"))
        return "image/vnd.tencent.tap";
    if (equal(ext, "tar"))
        return "application/x-tar";
    if (equal(ext, "tcap"))
        return "application/vnd.3gpp2.tcap";
    if (equal(ext, "tcl"))
        return "application/x-tcl";
    if (equal(ext, "td"))
        return "application/urc-targetdesc+xml";
    if (equal(ext, "teacher"))
        return "application/vnd.smart.teacher";
    if (equal(ext, "tei"))
        return "application/tei+xml";
    if (equal(ext, "teicorpus"))
        return "application/tei+xml";
    if (equal(ext, "tex"))
        return "application/x-tex";
    if (equal(ext, "texi"))
        return "application/x-texinfo";
    if (equal(ext, "texinfo"))
        return "application/x-texinfo";
    if (equal(ext, "text"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "tfi"))
        return "application/thraud+xml";
    if (equal(ext, "tfm"))
        return "application/x-tex-tfm";
    if (equal(ext, "tfx"))
        return "image/tiff-fx";
    if (equal(ext, "tga"))
        return "image/x-tga";
    if (equal(ext, "thmx"))
        return "application/vnd.ms-officetheme";
    if (equal(ext, "tif"))
        return "image/tiff";
    if (equal(ext, "tiff"))
        return "image/tiff";
    if (equal(ext, "tk"))
        return "application/x-tcl";
    if (equal(ext, "tmo"))
        return "application/vnd.tmobile-livetv";
    if (equal(ext, "toml"))
        return "application/toml";
    if (equal(ext, "torrent"))
        return "application/x-bittorrent";
    if (equal(ext, "tpl"))
        return "application/vnd.groove-tool-template";
    if (equal(ext, "tpt"))
        return "application/vnd.trid.tpt";
    if (equal(ext, "tr"))
        return "text/troff charset=UTF-8";
    if (equal(ext, "tra"))
        return "application/vnd.trueapp";
    if (equal(ext, "trig"))
        return "application/trig";
    if (equal(ext, "trm"))
        return "application/x-msterminal";
    if (equal(ext, "ts"))
        return "video/mp2t";
    if (equal(ext, "tsd"))
        return "application/timestamped-data";
    if (equal(ext, "tsv"))
        return "text/tab-separated-values charset=UTF-8";
    if (equal(ext, "ttc"))
        return "font/collection";
    if (equal(ext, "ttf"))
        return "font/ttf";
    if (equal(ext, "ttl"))
        return "text/turtle charset=UTF-8";
    if (equal(ext, "ttml"))
        return "application/ttml+xml";
    if (equal(ext, "twd"))
        return "application/vnd.simtech-mindmapper";
    if (equal(ext, "twds"))
        return "application/vnd.simtech-mindmapper";
    if (equal(ext, "txd"))
        return "application/vnd.genomatix.tuxedo";
    if (equal(ext, "txf"))
        return "application/vnd.mobius.txf";
    if (equal(ext, "txt"))
        return "text/plain charset=UTF-8";
    if (equal(ext, "u32"))
        return "application/x-authorware-bin";
    if (equal(ext, "u3d"))
        return "model/u3d";
    if (equal(ext, "u8dsn"))
        return "message/global-delivery-status";
    if (equal(ext, "u8hdr"))
        return "message/global-headers";
    if (equal(ext, "u8mdn"))
        return "message/global-disposition-notification";
    if (equal(ext, "u8msg"))
        return "message/global";
    if (equal(ext, "ubj"))
        return "application/ubjson";
    if (equal(ext, "udeb"))
        return "application/x-debian-package";
    if (equal(ext, "ufd"))
        return "application/vnd.ufdl";
    if (equal(ext, "ufdl"))
        return "application/vnd.ufdl";
    if (equal(ext, "ulx"))
        return "application/x-glulx";
    if (equal(ext, "umj"))
        return "application/vnd.umajin";
    if (equal(ext, "unityweb"))
        return "application/vnd.unity";
    if (equal(ext, "uo"))
        return "application/vnd.uoml+xml";
    if (equal(ext, "uoml"))
        return "application/vnd.uoml+xml";
    if (equal(ext, "uri"))
        return "text/uri-list charset=UTF-8";
    if (equal(ext, "uris"))
        return "text/uri-list charset=UTF-8";
    if (equal(ext, "urls"))
        return "text/uri-list charset=UTF-8";
    if (equal(ext, "usda"))
        return "model/vnd.usda";
    if (equal(ext, "usdz"))
        return "model/vnd.usdz+zip";
    if (equal(ext, "ustar"))
        return "application/x-ustar";
    if (equal(ext, "utz"))
        return "application/vnd.uiq.theme";
    if (equal(ext, "uu"))
        return "text/x-uuencode charset=UTF-8";
    if (equal(ext, "uva"))
        return "audio/vnd.dece.audio";
    if (equal(ext, "uvd"))
        return "application/vnd.dece.data";
    if (equal(ext, "uvf"))
        return "application/vnd.dece.data";
    if (equal(ext, "uvg"))
        return "image/vnd.dece.graphic";
    if (equal(ext, "uvh"))
        return "video/vnd.dece.hd";
    if (equal(ext, "uvi"))
        return "image/vnd.dece.graphic";
    if (equal(ext, "uvm"))
        return "video/vnd.dece.mobile";
    if (equal(ext, "uvp"))
        return "video/vnd.dece.pd";
    if (equal(ext, "uvs"))
        return "video/vnd.dece.sd";
    if (equal(ext, "uvt"))
        return "application/vnd.dece.ttml+xml";
    if (equal(ext, "uvu"))
        return "video/vnd.uvvu.mp4";
    if (equal(ext, "uvv"))
        return "video/vnd.dece.video";
    if (equal(ext, "uvva"))
        return "audio/vnd.dece.audio";
    if (equal(ext, "uvvd"))
        return "application/vnd.dece.data";
    if (equal(ext, "uvvf"))
        return "application/vnd.dece.data";
    if (equal(ext, "uvvg"))
        return "image/vnd.dece.graphic";
    if (equal(ext, "uvvh"))
        return "video/vnd.dece.hd";
    if (equal(ext, "uvvi"))
        return "image/vnd.dece.graphic";
    if (equal(ext, "uvvm"))
        return "video/vnd.dece.mobile";
    if (equal(ext, "uvvp"))
        return "video/vnd.dece.pd";
    if (equal(ext, "uvvs"))
        return "video/vnd.dece.sd";
    if (equal(ext, "uvvt"))
        return "application/vnd.dece.ttml+xml";
    if (equal(ext, "uvvu"))
        return "video/vnd.uvvu.mp4";
    if (equal(ext, "uvvv"))
        return "video/vnd.dece.video";
    if (equal(ext, "uvvx"))
        return "application/vnd.dece.unspecified";
    if (equal(ext, "uvvz"))
        return "application/vnd.dece.zip";
    if (equal(ext, "uvx"))
        return "application/vnd.dece.unspecified";
    if (equal(ext, "uvz"))
        return "application/vnd.dece.zip";
    if (equal(ext, "vbox"))
        return "application/x-virtualbox-vbox";
    if (equal(ext, "vbox-extpack"))
        return "application/x-virtualbox-vbox-extpack";
    if (equal(ext, "vcard"))
        return "text/vcard charset=UTF-8";
    if (equal(ext, "vcd"))
        return "application/x-cdlink";
    if (equal(ext, "vcf"))
        return "text/x-vcard charset=UTF-8";
    if (equal(ext, "vcg"))
        return "application/vnd.groove-vcard";
    if (equal(ext, "vcs"))
        return "text/x-vcalendar charset=UTF-8";
    if (equal(ext, "vcx"))
        return "application/vnd.vcx";
    if (equal(ext, "vdi"))
        return "application/x-virtualbox-vdi";
    if (equal(ext, "vds"))
        return "model/vnd.sap.vds";
    if (equal(ext, "vdx"))
        return "application/vnd.ms-visio.viewer";
    if (equal(ext, "vhd"))
        return "application/x-virtualbox-vhd";
    if (equal(ext, "vis"))
        return "application/vnd.visionary";
    if (equal(ext, "viv"))
        return "video/vnd.vivo";
    if (equal(ext, "vmdk"))
        return "application/x-virtualbox-vmdk";
    if (equal(ext, "vob"))
        return "video/x-ms-vob";
    if (equal(ext, "vor"))
        return "application/vnd.stardivision.writer";
    if (equal(ext, "vox"))
        return "application/x-authorware-bin";
    if (equal(ext, "vrml"))
        return "model/vrml";
    if (equal(ext, "vsd"))
        return "application/vnd.visio";
    if (equal(ext, "vsdx"))
        return "application/vnd.visio";
    if (equal(ext, "vsf"))
        return "application/vnd.vsf";
    if (equal(ext, "vss"))
        return "application/vnd.visio";
    if (equal(ext, "vst"))
        return "application/vnd.visio";
    if (equal(ext, "vsw"))
        return "application/vnd.visio";
    if (equal(ext, "vtf"))
        return "image/vnd.valve.source.texture";
    if (equal(ext, "vtt"))
        return "text/vtt charset=UTF-8";
    if (equal(ext, "vtu"))
        return "model/vnd.vtu";
    if (equal(ext, "vtx"))
        return "application/vnd.visio";
    if (equal(ext, "vxml"))
        return "application/voicexml+xml";
    if (equal(ext, "w3d"))
        return "application/x-director";
    if (equal(ext, "wad"))
        return "application/x-doom";
    if (equal(ext, "wadl"))
        return "application/vnd.sun.wadl+xml";
    if (equal(ext, "war"))
        return "application/java-archive";
    if (equal(ext, "wasm"))
        return "application/wasm";
    if (equal(ext, "wav"))
        return "audio/wav";
    if (equal(ext, "wax"))
        return "audio/x-ms-wax";
    if (equal(ext, "wbmp"))
        return "image/vnd.wap.wbmp";
    if (equal(ext, "wbs"))
        return "application/vnd.criticaltools.wbs+xml";
    if (equal(ext, "wbxml"))
        return "application/vnd.wap.wbxml";
    if (equal(ext, "wcm"))
        return "application/vnd.ms-works";
    if (equal(ext, "wdb"))
        return "application/vnd.ms-works";
    if (equal(ext, "wdp"))
        return "image/vnd.ms-photo";
    if (equal(ext, "weba"))
        return "audio/webm";
    if (equal(ext, "webapp"))
        return "application/x-web-app-manifest+json";
    if (equal(ext, "webm"))
        return "video/webm";
    if (equal(ext, "webmanifest"))
        return "application/manifest+json";
    if (equal(ext, "webp"))
        return "image/webp";
    if (equal(ext, "wg"))
        return "application/vnd.pmi.widget";
    if (equal(ext, "wgsl"))
        return "text/wgsl charset=UTF-8";
    if (equal(ext, "wgt"))
        return "application/widget";
    if (equal(ext, "wif"))
        return "application/watcherinfo+xml";
    if (equal(ext, "wks"))
        return "application/vnd.ms-works";
    if (equal(ext, "wm"))
        return "video/x-ms-wm";
    if (equal(ext, "wma"))
        return "audio/x-ms-wma";
    if (equal(ext, "wmd"))
        return "application/x-ms-wmd";
    if (equal(ext, "wmf"))
        return "application/x-msmetafile";
    if (equal(ext, "wml"))
        return "text/vnd.wap.wml charset=UTF-8";
    if (equal(ext, "wmlc"))
        return "application/vnd.wap.wmlc";
    if (equal(ext, "wmls"))
        return "text/vnd.wap.wmlscript charset=UTF-8";
    if (equal(ext, "wmlsc"))
        return "application/vnd.wap.wmlscriptc";
    if (equal(ext, "wmv"))
        return "video/x-ms-wmv";
    if (equal(ext, "wmx"))
        return "video/x-ms-wmx";
    if (equal(ext, "wmz"))
        return "application/x-ms-wmz";
    if (equal(ext, "woff"))
        return "font/woff";
    if (equal(ext, "woff2"))
        return "font/woff2";
    if (equal(ext, "wpd"))
        return "application/vnd.wordperfect";
    if (equal(ext, "wpl"))
        return "application/vnd.ms-wpl";
    if (equal(ext, "wps"))
        return "application/vnd.ms-works";
    if (equal(ext, "wqd"))
        return "application/vnd.wqd";
    if (equal(ext, "wri"))
        return "application/x-mswrite";
    if (equal(ext, "wrl"))
        return "model/vrml";
    if (equal(ext, "wsc"))
        return "message/vnd.wfa.wsc";
    if (equal(ext, "wsdl"))
        return "application/wsdl+xml";
    if (equal(ext, "wspolicy"))
        return "application/wspolicy+xml";
    if (equal(ext, "wtb"))
        return "application/vnd.webturbo";
    if (equal(ext, "wvx"))
        return "video/x-ms-wvx";
    if (equal(ext, "x32"))
        return "application/x-authorware-bin";
    if (equal(ext, "x3d"))
        return "model/x3d+xml";
    if (equal(ext, "x3db"))
        return "model/x3d+binary";
    if (equal(ext, "x3dbz"))
        return "model/x3d+binary";
    if (equal(ext, "x3dv"))
        return "model/x3d+vrml";
    if (equal(ext, "x3dvz"))
        return "model/x3d+vrml";
    if (equal(ext, "x3dz"))
        return "model/x3d+xml";
    if (equal(ext, "x_b"))
        return "model/vnd.parasolid.transmit.binary";
    if (equal(ext, "x_t"))
        return "model/vnd.parasolid.transmit.text";
    if (equal(ext, "xaml"))
        return "application/xaml+xml";
    if (equal(ext, "xap"))
        return "application/x-silverlight-app";
    if (equal(ext, "xar"))
        return "application/vnd.xara";
    if (equal(ext, "xav"))
        return "application/xcap-att+xml";
    if (equal(ext, "xbap"))
        return "application/x-ms-xbap";
    if (equal(ext, "xbd"))
        return "application/vnd.fujixerox.docuworks.binder";
    if (equal(ext, "xbm"))
        return "image/x-xbitmap";
    if (equal(ext, "xca"))
        return "application/xcap-caps+xml";
    if (equal(ext, "xcs"))
        return "application/calendar+xml";
    if (equal(ext, "xdcf"))
        return "application/vnd.gov.sk.xmldatacontainer+xml";
    if (equal(ext, "xdf"))
        return "application/xcap-diff+xml";
    if (equal(ext, "xdm"))
        return "application/vnd.syncml.dm+xml";
    if (equal(ext, "xdp"))
        return "application/vnd.adobe.xdp+xml";
    if (equal(ext, "xdssc"))
        return "application/dssc+xml";
    if (equal(ext, "xdw"))
        return "application/vnd.fujixerox.docuworks";
    if (equal(ext, "xel"))
        return "application/xcap-el+xml";
    if (equal(ext, "xenc"))
        return "application/xenc+xml";
    if (equal(ext, "xer"))
        return "application/patch-ops-error+xml";
    if (equal(ext, "xfdf"))
        return "application/vnd.adobe.xfdf";
    if (equal(ext, "xfdl"))
        return "application/vnd.xfdl";
    if (equal(ext, "xht"))
        return "application/xhtml+xml";
    if (equal(ext, "xhtm"))
        return "application/vnd.pwg-xhtml-print+xml";
    if (equal(ext, "xhtml"))
        return "application/xhtml+xml";
    if (equal(ext, "xhvml"))
        return "application/xv+xml";
    if (equal(ext, "xif"))
        return "image/vnd.xiff";
    if (equal(ext, "xla"))
        return "application/vnd.ms-excel";
    if (equal(ext, "xlam"))
        return "application/vnd.ms-excel.addin.macroenabled.12";
    if (equal(ext, "xlc"))
        return "application/vnd.ms-excel";
    if (equal(ext, "xlf"))
        return "application/x-xliff+xml";
    if (equal(ext, "xlm"))
        return "application/vnd.ms-excel";
    if (equal(ext, "xls"))
        return "application/vnd.ms-excel";
    if (equal(ext, "xlsb"))
        return "application/vnd.ms-excel.sheet.binary.macroenabled.12";
    if (equal(ext, "xlsm"))
        return "application/vnd.ms-excel.sheet.macroenabled.12";
    if (equal(ext, "xlsx"))
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    if (equal(ext, "xlt"))
        return "application/vnd.ms-excel";
    if (equal(ext, "xltm"))
        return "application/vnd.ms-excel.template.macroenabled.12";
    if (equal(ext, "xltx"))
        return "application/vnd.openxmlformats-officedocument.spreadsheetml.template";
    if (equal(ext, "xlw"))
        return "application/vnd.ms-excel";
    if (equal(ext, "xm"))
        return "audio/xm";
    if (equal(ext, "xml"))
        return "application/xml";
    if (equal(ext, "xns"))
        return "application/xcap-ns+xml";
    if (equal(ext, "xo"))
        return "application/vnd.olpc-sugar";
    if (equal(ext, "xop"))
        return "application/xop+xml";
    if (equal(ext, "xpi"))
        return "application/x-xpinstall";
    if (equal(ext, "xpl"))
        return "application/xproc+xml";
    if (equal(ext, "xpm"))
        return "image/x-xpixmap";
    if (equal(ext, "xpr"))
        return "application/vnd.is-xpr";
    if (equal(ext, "xps"))
        return "application/vnd.ms-xpsdocument";
    if (equal(ext, "xpw"))
        return "application/vnd.intercon.formnet";
    if (equal(ext, "xpx"))
        return "application/vnd.intercon.formnet";
    if (equal(ext, "xsd"))
        return "application/xml";
    if (equal(ext, "xsf"))
        return "application/prs.xsf+xml";
    if (equal(ext, "xsl"))
        return "application/xml";
    if (equal(ext, "xslt"))
        return "application/xslt+xml";
    if (equal(ext, "xsm"))
        return "application/vnd.syncml+xml";
    if (equal(ext, "xspf"))
        return "application/xspf+xml";
    if (equal(ext, "xul"))
        return "application/vnd.mozilla.xul+xml";
    if (equal(ext, "xvm"))
        return "application/xv+xml";
    if (equal(ext, "xvml"))
        return "application/xv+xml";
    if (equal(ext, "xwd"))
        return "image/x-xwindowdump";
    if (equal(ext, "xyz"))
        return "chemical/x-xyz";
    if (equal(ext, "xz"))
        return "application/x-xz";
    if (equal(ext, "yaml"))
        return "text/yaml charset=UTF-8";
    if (equal(ext, "yang"))
        return "application/yang";
    if (equal(ext, "yin"))
        return "application/yin+xml";
    if (equal(ext, "yml"))
        return "text/yaml charset=UTF-8";
    if (equal(ext, "ymp"))
        return "text/x-suse-ymp charset=UTF-8";
    if (equal(ext, "z1"))
        return "application/x-zmachine";
    if (equal(ext, "z2"))
        return "application/x-zmachine";
    if (equal(ext, "z3"))
        return "application/x-zmachine";
    if (equal(ext, "z4"))
        return "application/x-zmachine";
    if (equal(ext, "z5"))
        return "application/x-zmachine";
    if (equal(ext, "z6"))
        return "application/x-zmachine";
    if (equal(ext, "z7"))
        return "application/x-zmachine";
    if (equal(ext, "z8"))
        return "application/x-zmachine";
    if (equal(ext, "zaz"))
        return "application/vnd.zzazz.deck+xml";
    if (equal(ext, "zip"))
        return "application/x-zip-compressed";
    if (equal(ext, "zir"))
        return "application/vnd.zul";
    if (equal(ext, "zirz"))
        return "application/vnd.zul";
    if (equal(ext, "zmm"))
        return "application/vnd.handheld-entertainment+xml";

    /* Default */
    return "application/octet-stream";
}

static int equal(const char* str1, const char* str2) {
    return strcmp(str1, str2) == 0;
}

#endif
