/*
SQLyog Ultimate v10.00 Beta1
MySQL - 5.7.34-log : Database - flower_managerment
*********************************************************************
*/

/*!40101 SET NAMES utf8 */;

/*!40101 SET SQL_MODE=''*/;

/*!40014 SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0 */;
/*!40014 SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0 */;
/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='NO_AUTO_VALUE_ON_ZERO' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES, SQL_NOTES=0 */;
CREATE DATABASE /*!32312 IF NOT EXISTS*/`flower_managerment` /*!40100 DEFAULT CHARACTER SET utf8mb4 */;

USE `flower_managerment`;

/*Table structure for table `flower_info` */

DROP TABLE IF EXISTS `flower_info`;

CREATE TABLE `flower_info` (
  `id` varchar(255) NOT NULL,
  `type` varchar(255) DEFAULT NULL,
  `plantTime` varchar(255) DEFAULT NULL,
  `farming` varchar(255) DEFAULT NULL,
  `nongzi` varchar(255) DEFAULT NULL,
  `location1` varchar(255) DEFAULT NULL,
  `location2` varchar(255) DEFAULT NULL,
  `location3` varchar(255) DEFAULT NULL,
  `location4` varchar(255) DEFAULT NULL,
  `company` varchar(255) DEFAULT NULL,
  `contactPerson` varchar(255) DEFAULT NULL,
  `contactNum` varchar(255) DEFAULT NULL,
  `quantity` varchar(255) DEFAULT NULL,
  `costperPlant` double DEFAULT NULL,
  `cost` double DEFAULT NULL,
  `operator` varchar(255) DEFAULT NULL,
  `fertilization` varchar(255) DEFAULT NULL,
  `watering` varchar(255) DEFAULT NULL,
  `growth` varchar(255) DEFAULT NULL,
  `remark` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

/*Data for the table `flower_info` */

insert  into `flower_info`(`id`,`type`,`plantTime`,`farming`,`nongzi`,`location1`,`location2`,`location3`,`location4`,`company`,`contactPerson`,`contactNum`,`quantity`,`costperPlant`,`cost`,`operator`,`fertilization`,`watering`,`growth`,`remark`) values ('20210001','百合','2020/10/15',NULL,NULL,'114.04751673181558,32.453021090212324','114.04781673181557,32.453083138373145','114.04771673181558,32.45332109021233','114.04756555430082,32.453221090212324','登海五公司','李湖都','13152789082','871',0.8,696.8,'李湖都','缺少少量肥料','急缺水','C',NULL),('20210002','康乃馨','2020/08/05',NULL,NULL,'113.92085933675136,32.14876133063604','113.92115933675136,32.148817322259276','113.92110933675136,32.14901133063604','113.92092009954837,32.149061330636044','昂道江公司','褚华荆','15602296903','470',0.6,282,'褚华荆','缺少少量肥料','浇水情况正常','B+',NULL),('20210003','水仙','2020/09/11',NULL,NULL,'114.06104525931157,31.86492275229857','114.06129525931156,31.86495896815255','114.06124525931158,31.865122752298568','114.06111351097293,31.86517275229857','伍德府农业生产有限公司','钱光府','14746361085','839',0.5,419.5,'钱光府','缺少少量肥料','缺少量水','B',NULL),('20210004','郁金香','2020/12/11',NULL,NULL,'113.87911659369476,31.86785835168094','113.87941659369476,31.867940163110337','113.87931659369477,31.86805835168094','113.87921337754473,31.86805835168094','伍德杰佳有限公司','蓓瑗','15699302752','322',0.9,289.8,'蒋而饯','急缺肥料','急缺水','D',NULL),('20210005','玫瑰','2020/06/16',NULL,NULL,'113.76047294459343,32.37722853206222','113.76072294459343,32.37726336105458','113.76077294459343,32.37752853206222','113.76050510711922,32.37752853206222','伍德接农业生产有限公司','王雁华','13643945483','397',0.7,277.9,'蒋灵灵','急缺肥料','缺少量水','C',NULL),('20210006','康乃馨','2021/01/20',NULL,NULL,'114.11952118038526,32.07432179308168','114.11982118038526,32.07434390782365','114.11982118038526,32.07457179308168','114.11955310757291,32.07452179308168','农梦杰佳农业生产有限公司','卫慧华','13199988367','634',0.6,380.4,'李墟洪','急缺肥料','浇水情况正常','C+',NULL),('20210007','玫瑰','2020/09/12',NULL,NULL,'114.06208452081893,31.866470012553158','114.06233452081892,31.866555450001943','114.06228452081893,31.866670012553158','114.06209851124858,31.86672001255316','登海都农业生产有限公司','吴左华','14792518478','252',0.7,176.4,'吴引而','缺少少量肥料','急缺水','C',NULL),('20210008','水仙','2020/01/27',NULL,NULL,'113.91914266824593,32.14871121895815','113.91934266824593,32.14878620287247','113.91944266824592,32.14896121895815','113.91922821336208,32.14891121895815','博野衡公司','李慧馨','18654293471','456',0.5,228,'王天射','急缺肥料','浇水情况正常','C+',NULL),('20210009','水仙','2020/07/03',NULL,NULL,'113.93999830026665,32.32921066269605','113.94029830026665,32.32928422636885','113.94019830026666,32.32951066269605','113.94009463304317,32.32941066269605','博野郡有限公司','郑馨瑗','17609240275','932',0.5,466,'李斗翼','肥料情况正常','浇水情况正常','A',NULL),('20210010','康乃馨','2021/05/05',NULL,NULL,'113.83440728870485,32.47019722584462','113.83470728870485,32.47029716183582','113.83470728870485,32.47039722584462','113.83446962923952,32.470497225844625','伍德湖农业生产有限公司','李惠瑗','13164423765','811',0.6,486.6,'蒋襟荆','肥料情况正常','浇水情况正常','A',NULL),('20210011','百合','2020/07/23',NULL,NULL,'113.84754944331331,32.152933056881025','113.84774944331332,32.15295810996538','113.84784944331331,32.15323305688103','113.84756053730327,32.15323305688103','农梦而农业生产有限公司','李瑶瑶','17577433520','595',0.8,476,'卫故而','肥料情况正常','急缺水','C+',NULL),('20210012','玫瑰','2020/05/02',NULL,NULL,'113.87191780758363,32.31160540070166','113.87221780758362,32.311614227544226','113.87211780758363,32.31180540070166','113.87197056339363,32.31190540070166','伍德三农业生产有限公司','尤仪生','18756444250','188',0.7,131.6,'褚三豫','肥料情况正常','浇水情况正常','A',NULL),('20210013','郁金香','2021/05/16',NULL,NULL,'114.10778870157418,32.09270462852901','114.10803870157417,32.092794343878765','114.10808870157418,32.093004628529016','114.10784858003741,32.092954628529014','伍德三公司','蒋瑗荷','14518711522','466',0.9,419.4,'褚孺龙','肥料情况正常','缺少量水','B+',NULL),('20210014','康乃馨','2020/06/03',NULL,NULL,'114.09838475160979,32.30330288837762','114.09863475160978,32.303387306684904','114.09868475160978,32.303552888377624','114.09839035940796,32.303552888377624','伍德郡有限公司','何翠婕','15914477918','124',0.6,74.4,'李饯','肥料情况正常','急缺水','C+',NULL),('20210015','郁金香','2020/06/17',NULL,NULL,'114.75727977360064,32.49118617848677','114.75747977360065,32.4912841515786','114.75747977360065,32.491486178486774','114.75730829583938,32.49138617848677','农梦都公司','张瑗雁','13293008707','745',0.9,670.5,'李荆星','肥料情况正常','浇水情况正常','A',NULL),('20210016','康乃馨','2020/09/01',NULL,NULL,'114.06044433934943,32.12103508428975','114.06064433934944,32.12110198538316','114.06074433934943,32.121335084289754','114.06053553713674,32.12128508428975','登海轸农业生产有限公司','周淑梁','18602749245','642',0.6,385.2,'卫荆而','肥料情况正常','急缺水','C+',NULL),('20210017','康乃馨','2020/09/22',NULL,NULL,'114.08549956026037,32.23295283667015','114.08569956026038,32.233046714287696','114.08579956026037,32.23320283667015','114.08552893411176,32.23320283667015','农梦杰佳公司','钱慧俟','18660628727','856',0.6,513.6,'钱章子','肥料情况正常','浇水情况正常','A',NULL),('20210018','康乃馨','2021/05/25',NULL,NULL,'114.02647687654043,32.1844348652424','114.02672687654042,32.184435028169176','114.02677687654042,32.1846348652424','114.0265662179576,32.1846348652424','昂道都有限公司','许羊万','18317231516','701',0.6,420.6,'周郡墟','肥料情况正常','急缺水','C+',NULL),('20210019','百合','2020/02/18',NULL,NULL,'114.337539249994,32.330120254595705','114.33783924999399,32.3301231025019','114.337739249994,32.33037025459571','114.33760511573189,32.33037025459571','浓地农业生产有限公司','张仪蓓','18711931260','756',0.8,604.8,'王龙都','肥料情况正常','急缺水','C+',NULL),('20210020','郁金香','2020/10/07',NULL,NULL,'113.8887368053529,32.36443946355261','113.88893680535291,32.36450757746762','113.8889868053529,32.36473946355261','113.88879698958003,32.36463946355261','田园集市江公司','卫舌婵','15063879936','893',0.9,803.7,'郑轸地','肥料情况正常','缺少量水','B+',NULL),('20210021','玫瑰','2020/06/09',NULL,NULL,'113.81497036807464,32.15628917868129','113.81522036807463,32.156323119509786','113.81522036807463,32.15653917868129','113.81505109446555,32.15648917868129','登海湖有限公司','王羊左','15357731491','975',0.7,682.5,'赵洪墟','肥料情况正常','浇水情况正常','A',NULL),('20210022','百合','2020/03/05',NULL,NULL,'113.90506689504564,31.933015886922977','113.90526689504564,31.933027424561587','113.90531689504563,31.933315886922976','113.905153216942,31.933215886922977','登海故有限公司','蒋荷丘','13596891779','822',0.8,657.6,'蒋江翼','肥料情况正常','急缺水','C+',NULL),('20210023','郁金香','2020/04/05',NULL,NULL,'114.05423448417982,32.143427361203614','114.05453448417981,32.143487327390744','114.05443448417982,32.143677361203615','114.05428223879852,32.14372736120362','禾苗接农业生产有限公司','何万蓉','13752032389','922',0.9,829.8,'周物孺','肥料情况正常','缺少量水','B+',NULL),('20210024','水仙','2020/04/29',NULL,NULL,'114.02529041374265,32.18266062944597','114.02549041374266,32.18266095175243','114.02559041374265,32.18291062944597','114.02536703857896,32.18291062944597','禾苗杰佳有限公司','郑俟怡','17237462494','963',0.5,481.5,'韩斗翼','肥料情况正常','缺少量水','B+',NULL),('20210025','玫瑰','2021/04/05',NULL,NULL,'114.33841250261773,32.3299690100778','114.33866250261772,32.32997887068265','114.33861250261774,32.330169010077796','114.33844471832602,32.3302690100778','博野控有限公司','孙万华','13815773351','136',0.7,95.2,'李地杰','肥料情况正常','缺少量水','B+',NULL),('20210026','郁金香','2020/11/19',NULL,NULL,'114.1509138521628,32.05006016124394','114.1512138521628,32.05013284330062','114.1512138521628,32.050360161243944','114.15100062712149,32.05031016124394','禾土三公司','卫淑美','14759888597','746',0.9,671.4,'李地荆','肥料情况正常','急缺水','C+',NULL),('20210027','玫瑰','2020/08/20',NULL,NULL,'114.0586256234324,32.12243068498174','114.0589256234324,32.12248095815858','114.0589256234324,32.122630684981736','114.05866261979001,32.122630684981736','浓元公司','秦静羊','15237434678','387',0.7,270.9,'杨襟子','肥料情况正常','浇水情况正常','A',NULL),('20210028','玫瑰','2020/12/05',NULL,NULL,'114.06071871220546,32.1224155428774','114.06096871220545,32.12244925396238','114.06096871220545,32.1227155428774','114.06077080847435,32.1227155428774','昂道星农业生产有限公司','王婕梁','17584414677','855',0.7,598.5,'郑人星','肥料情况正常','缺少量水','B+',NULL),('20210029','水仙','2020/02/26',NULL,NULL,'114.11968491779426,31.872217529371703','114.11998491779426,31.872273931165516','114.11998491779426,31.872417529371702','114.11975323922636,31.872417529371702','禾土湖有限公司','蒋娜惠','17095186315','191',0.5,95.5,'沈墟光','肥料情况正常','急缺水','C+',NULL),('20210030','水仙','2020/01/09',NULL,NULL,'114.0628850994259,32.349410484618346','114.0630850994259,32.349466511235214','114.0631850994259,32.349610484618346','114.06297656661496,32.349610484618346','伍德江公司','钱慧蓉','18720538973','772',0.5,386,'李星新','肥料情况正常','浇水情况正常','A',NULL),('20210031','百合','2021/01/22',NULL,NULL,'113.8856011947337,32.35671753274304','113.8858011947337,32.35676964907667','113.88590119473369,32.35701753274304','113.8856318192055,32.35696753274304','田园集市府农业生产有限公司','尤梁丘','18319643669','646',0.8,516.8,'杨人衡','肥料情况正常','浇水情况正常','A',NULL),('20210032','百合','2020/11/02',NULL,NULL,'113.78538770560307,32.41595175174776','113.78563770560307,32.41603111630257','113.78558770560308,32.416201751747764','113.78540692096652,32.416251751747765','禾土翼农业生产有限公司','吕翠纨','13290814928','526',0.8,420.8,'钱越宝','肥料情况正常','浇水情况正常','A',NULL),('20210033','郁金香','2020/09/14',NULL,NULL,'113.9193084744161,32.30214320817903','113.91955847441609,32.30216536289201','113.9196084744161,32.30234320817903','113.91935892580729,32.30239320817903','绿分公司','何俟俟','18138071967','432',0.9,388.8,'赵地灵','肥料情况正常','浇水情况正常','A',NULL),('20210034','百合','2021/01/18',NULL,NULL,'113.78414197791245,32.00024026789172','113.78439197791245,32.00032278477085','113.78434197791246,32.00054026789172','113.78418212734744,32.00049026789172','农梦接有限公司','许生翠','15145692620','785',0.8,628,'冯三豫','肥料情况正常','浇水情况正常','A',NULL),('20210035','玫瑰','2020/04/12',NULL,NULL,'114.10633643028712,32.0922653861098','114.10653643028712,32.0923160654711','114.10663643028711,32.0925153861098','114.10638373046045,32.092565386109804','禾苗杰佳公司','何华万','17212002430','882',0.7,617.4,'卫宝襟','肥料情况正常','浇水情况正常','A',NULL),('20210036','康乃馨','2020/12/19',NULL,NULL,'114.09974374854689,32.30342705548348','114.09999374854688,32.30348141413754','114.10004374854688,32.303727055483485','114.09979227952701,32.303727055483485','禾土江有限公司','王左纨','13016790498','663',0.6,397.8,'郑射庐','肥料情况正常','浇水情况正常','A',NULL),('20210037','百合','2021/02/07',NULL,NULL,'114.91291316793883,31.840687983221603','114.91316316793882,31.840704385288117','114.91321316793882,31.840937983221604','114.91296066366449,31.840987983221602','田园集市襟农业生产有限公司','何馨惠','17752688796','359',0.8,287.2,'韩地府','肥料情况正常','浇水情况正常','A',NULL),('20210038','康乃馨','2021/02/13',NULL,NULL,'113.99045218531215,31.868508170031703','113.99075218531215,31.868526367112153','113.99070218531214,31.868758170031704','113.99051777463538,31.868758170031704','禾苗杰佳公司','卫婕延','18793524730','917',0.6,550.2,'蒋府宝','肥料情况正常','浇水情况正常','A',NULL),('20210039','郁金香','2020/01/26',NULL,NULL,'114.18450295053873,32.08206422836366','114.18470295053874,32.08210973257455','114.18480295053872,32.082364228363666','114.18458401618787,32.082314228363664','伍德控有限公司','李瑗东','15586658208','147',0.9,132.3,'李牛分','肥料情况正常','浇水情况正常','A',NULL),('20210040','水仙','2020/12/18',NULL,NULL,'114.19910391472841,32.11833796865088','114.19930391472842,32.118432402104304','114.1994039147284,32.11863796865088','114.19913775025321,32.11863796865088','绿星有限公司','李纨微','13896210211','474',0.5,237,'钱天五','肥料情况正常','浇水情况正常','A',NULL),('20210041','百合','2020/03/01',NULL,NULL,'114.08702347951835,32.3274853840704','114.08722347951836,32.32749435086669','114.08727347951834,32.3276853840704','114.08704246382479,32.3277353840704','登海新农业生产有限公司','钱静舌','13943616401','223',0.8,178.4,'李射越','肥料情况正常','浇水情况正常','A',NULL),('20210042','玫瑰','2020/10/11',NULL,NULL,'114.06815277055615,32.43957091626731','114.06835277055616,32.43961635955351','114.06840277055615,32.43987091626731','114.06816431128813,32.43977091626731','昂道故农业生产有限公司','吕美万','18616613812','795',0.7,556.5,'蒋洪星','肥料情况正常','浇水情况正常','A',NULL),('20210043','水仙','2020/11/12',NULL,NULL,'114.04800581497645,32.45371889117156','114.04820581497646,32.453813126765034','114.04825581497644,32.454018891171565','114.04803073458164,32.45391889117156','昂道地有限公司','施羊惠','18987080240','771',0.5,385.5,'张翼五','肥料情况正常','浇水情况正常','A',NULL),('20210044','水仙','2020/04/12',NULL,NULL,'113.8783014432883,31.867261210056498','113.87855144328829,31.867311370805993','113.87855144328829,31.867561210056497','113.8783631859264,31.867561210056497','昂道益有限公司','卫眉婵','18314013442','584',0.5,292,'李地饯','肥料情况正常','浇水情况正常','A',NULL),('20210045','水仙','2020/08/27',NULL,NULL,'114.04862712600358,32.4555651981055','114.04882712600359,32.45563685801735','114.04892712600358,32.4558651981055','114.04863974101323,32.4558151981055','登海衡农业生产有限公司','卫美眉','18113469730','464',0.5,232,'陈杰襟','肥料情况正常','浇水情况正常','A',NULL),('20210046','康乃馨','2020/01/18',NULL,NULL,'114.90017026980078,32.26886995393783','114.90047026980078,32.268949767832076','114.90047026980078,32.26906995393783','114.90025663362941,32.26906995393783','伍德府公司','施仪华','18687611875','484',0.6,290.4,'陈星华','肥料情况正常','浇水情况正常','A',NULL),('20210047','玫瑰','2020/10/21',NULL,NULL,'114.08625854099056,32.325133341821605','114.08645854099056,32.325227690934284','114.08645854099056,32.325333341821604','114.08630875946953,32.32543334182161','昂道翼有限公司','周生馨','13157150291','167',0.7,116.9,'李引衡','肥料情况正常','浇水情况正常','A',NULL),('20210048','玫瑰','2020/09/28',NULL,NULL,'113.81618491444851,32.15572235785841','113.81638491444852,32.15581658938474','113.81638491444852,32.15597235785841','113.81625407760532,32.15597235785841','禾土元有限公司','孙美婕','14925093798','848',0.7,593.6,'周分庐','肥料情况正常','浇水情况正常','A',NULL),('20210049','郁金香','2020/02/24',NULL,NULL,'113.98848457114799,31.868647477475697','113.98873457114799,31.868657767673408','113.98878457114799,31.868947477475697','113.9885150849272,31.868847477475697','禾土轸公司','韩梁珠','18878673022','361',0.9,324.9,'卫华','肥料情况正常','浇水情况正常','A',NULL),('20210050','水仙','2021/03/14',NULL,NULL,'114.19154507747136,32.118592644328004','114.19179507747135,32.11867044249963','114.19184507747136,32.118842644328005','114.19158343294423,32.118842644328005','绿衡公司','朱婕梁','18617194536','982',0.5,491,'孙章分','肥料情况正常','浇水情况正常','A',NULL),('20210051','玫瑰','2020/01/13',NULL,NULL,'114.06722223391192,32.439598540934874','114.06752223391192,32.4396246824054','114.06752223391192,32.43979854093487','114.06728353349762,32.43989854093488','伍德都公司','韩荷梁','14751381155','267',0.7,186.9,'孙宝分','肥料情况正常','浇水情况正常','A',NULL),('20210052','百合','2020/09/21',NULL,NULL,'113.91855876079539,32.14757150477271','113.91880876079539,32.147619222435004','113.9187587607954,32.14777150477271','113.9185718306977,32.147871504772716','田园集市带有限公司','陈婵慧','17316530296','408',0.8,326.4,'王而五','肥料情况正常','浇水情况正常','A',NULL),('20210053','郁金香','2020/01/19',NULL,NULL,'114.06377245531944,32.36344344935008','114.06402245531943,32.363467498382974','114.06402245531943,32.36364344935008','114.06385042879563,32.36369344935008','禾苗郡农业生产有限公司','郑怡珠','15854972164','958',0.9,862.2,'吴天越','肥料情况正常','浇水情况正常','A',NULL),('20210054','百合','2021/01/14',NULL,NULL,'114.28330517709959,32.13019347748565','114.2835051770996,32.130274922852664','114.2835051770996,32.13044347748565','114.28333770804912,32.13044347748565','田园集市杰佳有限公司','李露丘','13852310310','406',0.8,324.8,'李杰斗','肥料情况正常','浇水情况正常','A',NULL),('20210055','水仙','2021/03/23',NULL,NULL,'113.92006867655341,32.30441975775619','113.92026867655342,32.30445306804736','113.92026867655342,32.304719757756196','113.92014514813046,32.304669757756194','鲜湖有限公司','卫蓉丘','13290820714','869',0.5,434.5,'周牛襟','肥料情况正常','浇水情况正常','A',NULL),('20210056','玫瑰','2020/12/17',NULL,NULL,'114.17965745409174,32.276187846567446','114.17985745409175,32.27619654278168','114.17995745409173,32.27643784656745','114.17969307881212,32.27648784656745','农梦接公司','沈婕美','18016241321','609',0.7,426.3,'王新引','肥料情况正常','浇水情况正常','A',NULL),('20210057','郁金香','2020/03/11',NULL,NULL,'114.07167851035601,32.30610578819442','114.071978510356,32.30616127775067','114.071928510356,32.306405788194425','114.07172726890788,32.30630578819442','昂道杰佳公司','李巧眉','15812195239','289',0.9,260.1,'蒋而牛','肥料情况正常','浇水情况正常','A',NULL),('20210058','百合','2020/03/09',NULL,NULL,'114.118128966705,31.810132459548402','114.118428966705,31.810174086651855','114.118428966705,31.8104324595484','114.11818623946417,31.810332459548402','博野新有限公司','秦珠慧','15259612294','448',0.8,358.4,'吴郡墟','缺少少量肥料','浇水情况正常','B+',NULL),('20210059','水仙','2021/02/15',NULL,NULL,'113.87034184756418,32.312148413014015','113.87054184756418,32.312215999399534','113.87059184756417,32.312398413014016','113.87035594085391,32.31244841301402','登海洪农业生产有限公司','卫徐地','14592689859','348',0.5,174,'卫徐地','缺少少量肥料','浇水情况正常','B+',NULL),('20210060','郁金香','2020/01/12',NULL,NULL,'114.10642286952584,32.091532836883204','114.10662286952585,32.09158272717893','114.10667286952584,32.091832836883206','114.1064423514893,32.091832836883206','登海三公司','李襟越','13563587062','210',0.9,189,'李襟越','肥料情况正常','浇水情况正常','A',NULL),('20210061','康乃馨','2021/02/11',NULL,NULL,'113.96481365774223,31.904311906939697','113.96506365774222,31.90431779657483','113.96501365774223,31.904561906939698','113.96482153904459,31.904611906939696','浓地公司','郑引荆','15387483114','323',0.6,193.8,'郑引荆','急缺肥料','浇水情况正常','C+',NULL),('20210062','水仙','2020/07/05',NULL,NULL,'114.01350493573776,32.32244629790326','114.01370493573776,32.32245077492268','114.01375493573775,32.322746297903265','114.0135709515655,32.32264629790326','禾土五有限公司','孙蛮人','14765968867','511',0.5,255.5,'孙蛮人','急缺肥料','浇水情况正常','C+',NULL),('20210063','玫瑰','2020/05/29',NULL,NULL,'114.20688122302889,32.33619321231043','114.2070812230289,32.336216741555376','114.2070812230289,32.336393212310426','114.20689352380472,32.33649321231043','浓翼农业生产有限公司','褚地引','17651506056','144',0.7,100.8,'褚地引','急缺肥料','浇水情况正常','C+',NULL),('20210064','水仙','2020/06/29',NULL,NULL,'113.77038840349071,32.348456966172314','113.77068840349071,32.34845705367763','113.77068840349071,32.34875696617232','113.77039116791073,32.34875696617232','禾土府农业生产有限公司','王牛灵','18036967171','229',0.5,114.5,'王牛灵','急缺肥料','浇水情况正常','C+',NULL),('20210065','水仙','2020/07/11',NULL,NULL,'114.1135079106681,32.07618882209691','114.11370791066811,32.076242134284094','114.1137579106681,32.07648882209691','114.11356347690464,32.07648882209691','禾土杰佳有限公司','王孺','15835108054','231',0.5,115.5,'王孺','急缺肥料','浇水情况正常','C+',NULL),('20210066','玫瑰','2020/12/06',NULL,NULL,'114.24273331044661,32.21689483886565','114.2429833104466,32.21695006533424','114.2430333104466,32.21709483886565','114.24283248840041,32.21714483886565','禾苗元公司','冯物五','13059062612','868',0.7,607.6,'冯物五','肥料情况正常','浇水情况正常','A',NULL),('20210067','水仙','2020/09/01',NULL,NULL,'113.87941069714827,32.228007935525966','113.87966069714827,32.22802202234898','113.87971069714827,32.228207935525965','113.87944345832182,32.22825793552597','鲜故公司','钱人墟','14901335872','244',0.5,122,'钱人墟','缺少少量肥料','浇水情况正常','B+',NULL),('20210068','百合','2020/05/01',NULL,NULL,'114.13956209072293,32.3969188459192','114.13976209072294,32.39698157417602','114.13981209072293,32.3971188459192','114.1396284050318,32.397168845919204','禾苗五公司','陈郡引','18272182060','479',0.8,383.2,'陈郡引','急缺肥料','浇水情况正常','C+',NULL),('20210069','百合','2020/10/22',NULL,NULL,'113.84429146230245,32.56413027159395','113.84459146230245,32.56413956770817','113.84449146230246,32.564430271593956','113.84430372394908,32.56433027159395','鲜府农业生产有限公司','钱豫章','18035243288','256',0.8,204.8,'钱豫章','缺少少量肥料','浇水情况正常','B+',NULL),('20210070','康乃馨','2021/01/02',NULL,NULL,'114.05564884542348,32.47763504214315','114.05594884542347,32.47766480230239','114.05584884542348,32.47788504214315','114.05571393518896,32.47788504214315','禾苗分有限公司','褚故射','14751344978','918',0.6,550.8,'褚故射','急缺肥料','浇水情况正常','C+',NULL),('20210071','百合','2020/07/29',NULL,NULL,'114.15798656451297,32.14434305346144','114.15828656451296,32.14442295019339','114.15823656451296,32.144643053461444','114.158064928926,32.14459305346144','禾土接农业生产有限公司','郑控而','13528878314','959',0.8,767.2,'郑控而','急缺肥料','浇水情况正常','C+',NULL),('20210072','百合','2020/10/10',NULL,NULL,'113.91862699041504,32.54907632181798','113.91892699041503,32.54908558104075','113.91892699041503,32.54927632181798','113.91865429978476,32.54937632181798','农梦都公司','蒋墟衡','17136549908','454',0.8,363.2,'蒋墟衡','肥料情况正常','浇水情况正常','A',NULL),('20210073','百合','2020/09/10',NULL,NULL,'114.06034353255176,31.867064490657384','114.06054353255176,31.867127539639274','114.06064353255175,31.867314490657385','114.06035732809416,31.867264490657384','浓衡有限公司','赵华庐','13247667739','755',0.8,604,'赵华庐','肥料情况正常','浇水情况正常','A',NULL),('20210074','水仙','2020/12/05',NULL,NULL,'113.8019116725401,32.51246111563166','113.80211167254011,32.512492916938086','113.8022116725401,32.51271111563166','113.80201094329738,32.51271111563166','农梦而公司','韩襟翼','18662328615','443',0.5,221.5,'韩襟翼','急缺肥料','浇水情况正常','C+',NULL),('20210075','郁金香','2020/07/23',NULL,NULL,'114.99517994669571,32.55693312075405','114.99537994669572,32.556974244582904','114.99537994669572,32.557183120754054','114.99524002090169,32.557233120754056','田园集市而农业生产有限公司','蒋郡越','15804989600','635',0.9,571.5,'蒋郡越','缺少少量肥料','浇水情况正常','B+',NULL),('20210076','郁金香','2021/03/01',NULL,NULL,'113.78471410426224,31.999384983203527','113.78496410426223,31.999416764510677','113.78496410426223,31.999634983203528','113.784742926046,31.999584983203526','登海控有限公司','陈襟新','13041204188','762',0.9,685.8,'陈襟新','急缺肥料','浇水情况正常','C+',NULL),('20210077','百合','2021/05/05',NULL,NULL,'114.90121574870754,32.26823518839607','114.90146574870754,32.26827829426533','114.90141574870755,32.26853518839607','114.90121731509868,32.26843518839607','农梦翼公司','沈府襟','14779786371','452',0.8,361.6,'沈府襟','缺少少量肥料','急缺水','C',NULL),('20210078','水仙','2021/03/17',NULL,NULL,'114.04108192747272,32.10956179232468','114.04133192747271,32.1096021473301','114.04128192747272,32.109811792324685','114.0411115799166,32.109811792324685','田园集市三公司','王华','14750932025','489',0.5,244.5,'王华','缺少少量肥料','缺少量水','B',NULL),('20210079','郁金香','2020/03/15',NULL,NULL,'114.02721719408441,32.161896747347186','114.02741719408442,32.161982137913874','114.02751719408441,32.16219674734719','114.02725732052929,32.162096747347185','鲜星有限公司','周庐斗','18060849007','553',0.9,497.7,'周庐斗','肥料情况正常','急缺水','C+',NULL),('20210080','玫瑰','2020/01/14',NULL,NULL,'114.14080092829089,32.395195773673514','114.1410009282909,32.39527365710675','114.1410009282909,32.395445773673515','114.14087168485746,32.39549577367352','博野翼公司','陈星子','18558666971','736',0.7,515.2,'陈星子','急缺肥料','急缺水','D',NULL),('20210081','百合','2020/11/21',NULL,NULL,'114.15767216080953,32.16471688517838','114.15792216080952,32.16474955993488','114.15787216080953,32.16491688517838','114.15773611554849,32.16496688517838','田园集市襟公司','陈翼射','17578594607','428',0.8,342.4,'陈翼射','急缺肥料','急缺水','D',NULL),('20210082','百合','2020/09/04',NULL,NULL,'113.90768468088234,31.93458621689458','113.90793468088233,31.934623611276397','113.90788468088235,31.93483621689458','113.90771246373069,31.93488621689458','博野益有限公司','陈星之','13940398244','146',0.8,116.8,'陈星之','急缺肥料','浇水情况正常','C+',NULL),('20210083','郁金香','2020/01/03',NULL,NULL,'113.91992833847479,32.30477922046124','113.92017833847478,32.3047879699394','113.92017833847478,32.305079220461245','113.91994866532673,32.30502922046124','禾苗湖公司','李蛮而','13494919642','333',0.9,299.7,'李蛮而','肥料情况正常','缺少量水','B+',NULL),('20210084','水仙','2021/01/27',NULL,NULL,'114.00995011822388,31.799561651477134','114.01015011822389,31.799647197647467','114.01025011822388,31.799761651477134','114.00997466466595,31.799811651477135','昂道襟有限公司','陈杰蛮','17626405690','812',0.5,406,'陈杰蛮','急缺肥料','浇水情况正常','C+',NULL),('20210085','百合','2020/04/26',NULL,NULL,'114.02511811005185,32.184698421400576','114.02541811005185,32.18475510905869','114.02536811005184,32.18494842140058','114.02512645792926,32.18499842140058','农梦庐有限公司','陈江湖','14770972598','940',0.8,752,'陈江湖','急缺肥料','缺少量水','C',NULL),('20210086','水仙','2020/06/25',NULL,NULL,'113.97311500225389,32.18679480276789','113.97341500225389,32.18681039930014','113.9733150022539,32.18699480276789','113.9731256775459,32.18704480276789','昂道洪农业生产有限公司','周越宝','18150791021','185',0.5,92.5,'周越宝','缺少少量肥料','浇水情况正常','B+',NULL),('20210087','百合','2020/11/10',NULL,NULL,'113.96430560166017,31.90378361223242','113.96455560166017,31.903846458878295','113.96460560166017,31.90398361223242','113.96434066232688,31.90408361223242','浓带农业生产有限公司','卫子轸','13712892458','129',0.8,103.2,'卫子轸','肥料情况正常','缺少量水','B+',NULL),('20210088','百合','2020/09/30',NULL,NULL,'113.96594177433012,31.96978449992401','113.96624177433011,31.969812169144305','113.96624177433011,31.97008449992401','113.966022289857,31.97008449992401','鲜翼农业生产有限公司','韩蛮洪','17739006998','199',0.8,159.2,'韩蛮洪','急缺肥料','浇水情况正常','C+',NULL),('20210089','百合','2020/09/09',NULL,NULL,'113.80098739263391,32.51218963172633','113.80123739263391,32.512271845960505','113.80118739263392,32.51248963172633','113.80105210238179,32.51248963172633','浓而公司','卫新接','18044049920','881',0.8,704.8,'卫新接','肥料情况正常','急缺水','C+',NULL),('20210090','郁金香','2020/05/13',NULL,NULL,'113.9646208129339,31.90306486869203','113.9648708129339,31.90314405937392','113.9649208129339,31.903314868692032','113.96467921802999,31.903314868692032','昂道三农业生产有限公司','杨人华','17731365815','354',0.9,318.6,'杨人华','缺少少量肥料','急缺水','C',NULL),('20210091','康乃馨','2020/11/27',NULL,NULL,'114.13665213274109,31.9490157033453','114.1368521327411,31.949086116271303','114.1368521327411,31.9493157033453','114.13674932631123,31.9492657033453','登海府公司','卫翼翼','18229023319','846',0.6,507.6,'卫翼翼','缺少少量肥料','缺少量水','B',NULL),('20210092','玫瑰','2021/05/21',NULL,NULL,'113.83951222541766,32.22705784659701','113.83971222541767,32.22713982151771','113.83971222541767,32.227357846597016','113.83952999591892,32.227307846597014','禾土带有限公司','孙豫豫','13820661843','557',0.7,389.9,'孙豫豫','急缺肥料','急缺水','D',NULL),('20210093','玫瑰','2020/01/16',NULL,NULL,'113.83923564628559,32.22891469728379','113.8394356462856,32.22895738603544','113.83948564628558,32.22916469728379','113.83931057173024,32.22916469728379','禾土衡农业生产有限公司','蒋地人','15970571344','365',0.7,255.5,'蒋地人','缺少少量肥料','缺少量水','B',NULL),('20210094','康乃馨','2021/02/11',NULL,NULL,'114.05527334445429,32.476818342401685','114.0554733444543,32.47683507667112','114.05557334445429,32.47711834240169','114.05531053178564,32.47706834240169','绿而公司','王瓯故','13523236598','453',0.6,271.8,'王瓯故','缺少少量肥料','急缺水','C',NULL),('20210095','郁金香','2020/11/16',NULL,NULL,'113.78388699166545,32.417248456323044','113.78418699166545,32.41734389317292','113.78418699166545,32.417498456323045','113.78388797577142,32.41754845632305','博野府有限公司','褚光饯','13583280531','532',0.9,478.8,'褚光饯','缺少少量肥料','浇水情况正常','B+',NULL),('20210096','玫瑰','2020/11/06',NULL,NULL,'114.17725936834925,32.2753664068336','114.17755936834925,32.275414411463046','114.17750936834925,32.2755664068336','114.17732128891575,32.2756664068336','登海三公司','张洪地','15279442392','217',0.7,151.9,'张洪地','缺少少量肥料','急缺水','C',NULL),('20210097','水仙','2021/01/17',NULL,NULL,'114.19916809174018,32.11799273373983','114.19941809174017,32.11807674515839','114.19936809174018,32.118292733739835','114.19924604528825,32.118242733739834','禾苗杰佳有限公司','张都衡','18747873354','510',0.5,255,'张都衡','肥料情况正常','浇水情况正常','A',NULL),('20210098','康乃馨','2021/03/26',NULL,NULL,'114.06289796148253,32.34944122776086','114.06319796148253,32.349501325873575','114.06309796148254,32.349691227760864','114.06298714059272,32.349741227760866','农梦府公司','郑三接','17727546035','860',0.6,516,'郑三接','缺少少量肥料','急缺水','C',NULL),('20210099','水仙','2021/04/20',NULL,NULL,'114.13753201211219,31.94848038333413','114.13778201211218,31.948542814234862','114.1377320121122,31.948780383334128','114.13756554763388,31.948780383334128','登海故公司','赵之华','13191153457','243',0.5,121.5,'赵之华','急缺肥料','急缺水','D',NULL);

/*Table structure for table `operator_info` */

DROP TABLE IF EXISTS `operator_info`;

CREATE TABLE `operator_info` (
  `UserId` varchar(150) NOT NULL,
  `Password` varchar(150) NOT NULL,
  `Master` varchar(50) NOT NULL,
  PRIMARY KEY (`UserId`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4;

/*Data for the table `operator_info` */

insert  into `operator_info`(`UserId`,`Password`,`Master`) values ('111','111','1'),('123','123','0');

/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;
/*!40014 SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS */;
/*!40014 SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS */;
/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
