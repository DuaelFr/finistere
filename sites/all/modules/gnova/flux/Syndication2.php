<?php
class getFieldsSearch {
  public $idModule; // string
}

class getFieldsSearchResponse {
  public $getFieldsSearchResult; // getFieldsSearchResult
}

class getFieldsSearchResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getFieldsListing {
  public $idModule; // string
}

class getFieldsListingResponse {
  public $getFieldsListingResult; // getFieldsListingResult
}

class getFieldsListingResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getFieldsDetail {
  public $idModule; // string
}

class getFieldsDetailResponse {
  public $getFieldsDetailResult; // getFieldsDetailResult
}

class getFieldsDetailResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getListing {
  public $idModule; // string
}

class getListingResponse {
  public $getListingResult; // getListingResult
}

class getListingResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getListingDiff {
  public $idModule; // string
  public $date; // string
}

class getListingDiffResponse {
  public $getListingDiffResult; // getListingDiffResult
}

class getListingDiffResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getListingByIDs {
  public $idModule; // string
  public $ObjetTourCode; // string
  public $IDs; // string
}

class getListingByIDsResponse {
  public $getListingByIDsResult; // getListingByIDsResult
}

class getListingByIDsResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getListingWithSearch {
  public $idModule; // string
  public $FieldsSearch; // FieldsSearch
}

class FieldsSearch {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getListingWithSearchResponse {
  public $getListingWithSearchResult; // getListingWithSearchResult
}

class getListingWithSearchResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getListElements {
  public $idModule; // string
  public $FORMFIELD_ID; // string
  public $VALEUR_PARENT; // string
}

class getListElementsResponse {
  public $getListElementsResult; // getListElementsResult
}

class getListElementsResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getDetail {
  public $idModule; // string
  public $idOffre; // string
  public $OBJETTOUR_CODE; // string
}

class getDetailResponse {
  public $getDetailResult; // getDetailResult
}

class getDetailResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getDetailBordereau {
  public $idModule; // string
  public $OBJETTOUR_CODE; // string
}

class getDetailBordereauResponse {
  public $getDetailBordereauResult; // getDetailBordereauResult
}

class getDetailBordereauResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getDetailBordereauDiff {
  public $idModule; // string
  public $OBJETTOUR_CODE; // string
  public $date; // string
}

class getDetailBordereauDiffResponse {
  public $getDetailBordereauDiffResult; // getDetailBordereauDiffResult
}

class getDetailBordereauDiffResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getOffresSuppr {
  public $idModule; // string
  public $date; // string
}

class getOffresSupprResponse {
  public $getOffresSupprResult; // getOffresSupprResult
}

class getOffresSupprResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getDetailBordereauSuppr {
  public $idModule; // string
  public $OBJETTOUR_CODE; // string
  public $date; // string
}

class getDetailBordereauSupprResponse {
  public $getDetailBordereauSupprResult; // getDetailBordereauSupprResult
}

class getDetailBordereauSupprResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getStructures {
  public $idModule; // string
}

class getStructuresResponse {
  public $getStructuresResult; // getStructuresResult
}

class getStructuresResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getResearch {
  public $idModule; // string
}

class getResearchResponse {
  public $getResearchResult; // getResearchResult
}

class getResearchResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getResearchWithSearch {
  public $idModule; // string
  public $FieldsSearch; // FieldsSearch
}

class getResearchWithSearchResponse {
  public $getResearchWithSearchResult; // getResearchWithSearchResult
}

class getResearchWithSearchResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getDispo {
  public $idModule; // string
  public $idOffre; // string
  public $OBJETTOUR_CODE; // string
}

class getDispoResponse {
  public $getDispoResult; // getDispoResult
}

class getDispoResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class getDispoBordereau {
  public $idModule; // string
  public $OBJETTOUR_CODE; // string
}

class getDispoBordereauResponse {
  public $getDispoBordereauResult; // getDispoBordereauResult
}

class getDispoBordereauResult {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}

class DataSet {
  public $schema; // <anyXML>
  public $any; // <anyXML>
}


/**
 * Syndication2 class
 *
 *
 *
 * @author    {author}
 * @copyright {copyright}
 * @package   {package}
 */
class Syndication2 extends SoapClient {

  private static $classmap = array(
    'getFieldsSearch'                 => 'getFieldsSearch',
    'getFieldsSearchResponse'         => 'getFieldsSearchResponse',
    'getFieldsSearchResult'           => 'getFieldsSearchResult',
    'getFieldsListing'                => 'getFieldsListing',
    'getFieldsListingResponse'        => 'getFieldsListingResponse',
    'getFieldsListingResult'          => 'getFieldsListingResult',
    'getFieldsDetail'                 => 'getFieldsDetail',
    'getFieldsDetailResponse'         => 'getFieldsDetailResponse',
    'getFieldsDetailResult'           => 'getFieldsDetailResult',
    'getListing'                      => 'getListing',
    'getListingResponse'              => 'getListingResponse',
    'getListingResult'                => 'getListingResult',
    'getListingDiff'                  => 'getListingDiff',
    'getListingDiffResponse'          => 'getListingDiffResponse',
    'getListingDiffResult'            => 'getListingDiffResult',
    'getListingByIDs'                 => 'getListingByIDs',
    'getListingByIDsResponse'         => 'getListingByIDsResponse',
    'getListingByIDsResult'           => 'getListingByIDsResult',
    'getListingWithSearch'            => 'getListingWithSearch',
    'FieldsSearch'                    => 'FieldsSearch',
    'getListingWithSearchResponse'    => 'getListingWithSearchResponse',
    'getListingWithSearchResult'      => 'getListingWithSearchResult',
    'getListElements'                 => 'getListElements',
    'getListElementsResponse'         => 'getListElementsResponse',
    'getListElementsResult'           => 'getListElementsResult',
    'getDetail'                       => 'getDetail',
    'getDetailResponse'               => 'getDetailResponse',
    'getDetailResult'                 => 'getDetailResult',
    'getDetailBordereau'              => 'getDetailBordereau',
    'getDetailBordereauResponse'      => 'getDetailBordereauResponse',
    'getDetailBordereauResult'        => 'getDetailBordereauResult',
    'getDetailBordereauDiff'          => 'getDetailBordereauDiff',
    'getDetailBordereauDiffResponse'  => 'getDetailBordereauDiffResponse',
    'getDetailBordereauDiffResult'    => 'getDetailBordereauDiffResult',
    'getOffresSuppr'                  => 'getOffresSuppr',
    'getOffresSupprResponse'          => 'getOffresSupprResponse',
    'getOffresSupprResult'            => 'getOffresSupprResult',
    'getDetailBordereauSuppr'         => 'getDetailBordereauSuppr',
    'getDetailBordereauSupprResponse' => 'getDetailBordereauSupprResponse',
    'getDetailBordereauSupprResult'   => 'getDetailBordereauSupprResult',
    'getStructures'                   => 'getStructures',
    'getStructuresResponse'           => 'getStructuresResponse',
    'getStructuresResult'             => 'getStructuresResult',
    'getResearch'                     => 'getResearch',
    'getResearchResponse'             => 'getResearchResponse',
    'getResearchResult'               => 'getResearchResult',
    'getResearchWithSearch'           => 'getResearchWithSearch',
    'getResearchWithSearchResponse'   => 'getResearchWithSearchResponse',
    'getResearchWithSearchResult'     => 'getResearchWithSearchResult',
    'getDispo'                        => 'getDispo',
    'getDispoResponse'                => 'getDispoResponse',
    'getDispoResult'                  => 'getDispoResult',
    'getDispoBordereau'               => 'getDispoBordereau',
    'getDispoBordereauResponse'       => 'getDispoBordereauResponse',
    'getDispoBordereauResult'         => 'getDispoBordereauResult',
    'DataSet'                         => 'DataSet',
  );

  public function Syndication2($wsdl = "syndication2.asmx.xml", $options = array()) {
    foreach (self::$classmap as $key => $value) {
      if (!isset($options['classmap'][$key])) {
        $options['classmap'][$key] = $value;
      }
    }
    parent::__construct($wsdl, $options);
  }

  /**
   * Renvoie un Dataset qui contient tous les champs du formulaire de recherche.
   *
   * @param getFieldsSearch $parameters
   * @return getFieldsSearchResponse
   */
  public function getFieldsSearch(getFieldsSearch $parameters) {
    return $this->__soapCall('getFieldsSearch', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient tous les champs du listing.
   *
   * @param getFieldsListing $parameters
   * @return getFieldsListingResponse
   */
  public function getFieldsListing(getFieldsListing $parameters) {
    return $this->__soapCall('getFieldsListing', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient tous les champs du detail.
   *
   * @param getFieldsDetail $parameters
   * @return getFieldsDetailResponse
   */
  public function getFieldsDetail(getFieldsDetail $parameters) {
    return $this->__soapCall('getFieldsDetail', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le listing des offres sans avoir fait de recherche.
   *
   * @param getListing $parameters
   * @return getListingResponse
   */
  public function getListing(getListing $parameters) {
    var_dump($parameters);
    return $this->__soapCall('getListing', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le listing des offres créées ou modifiées depuis la
   * date indiquée.
   *
   * @param getListingDiff $parameters
   * @return getListingDiffResponse
   */
  public function getListingDiff(getListingDiff $parameters) {
    return $this->__soapCall('getListingDiff', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le listing des offres en fonction d'IDs ex : HPAMIP0430000116,HPAMIP0430000116.
   *
   *
   * @param getListingByIDs $parameters
   * @return getListingByIDsResponse
   */
  public function getListingByIDs(getListingByIDs $parameters) {
    return $this->__soapCall('getListingByIDs', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le listing des offres en fonction des champs de recherche.
   * Le DataSet passé en paramètre correspond à la structure du DataSet renvoyé par la
   * méthode getFieldsSearch.
   *
   * @param getListingWithSearch $parameters
   * @return getListingWithSearchResponse
   */
  public function getListingWithSearch(getListingWithSearch $parameters) {
    return $this->__soapCall('getListingWithSearch', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient tous les éléments d'une liste dont le champ est passé
   * en paramètre. Si le champ dépend d'un autre champ, la valeur du champ parent est à
   * renseigner.
   *
   * @param getListElements $parameters
   * @return getListElementsResponse
   */
  public function getListElements(getListElements $parameters) {
    return $this->__soapCall('getListElements', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le detail d'une offre.
   *
   * @param getDetail $parameters
   * @return getDetailResponse
   */
  public function getDetail(getDetail $parameters) {
    return $this->__soapCall('getDetail', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le detail d'un bordereau.
   *
   * @param getDetailBordereau $parameters
   * @return getDetailBordereauResponse
   */
  public function getDetailBordereau(getDetailBordereau $parameters) {
    return $this->__soapCall('getDetailBordereau', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le détail des offres créées ou modifiées depuis la
   * date indiquée.
   *
   * @param getDetailBordereauDiff $parameters
   * @return getDetailBordereauDiffResponse
   */
  public function getDetailBordereauDiff(getDetailBordereauDiff $parameters) {
    return $this->__soapCall('getDetailBordereauDiff', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient la liste des offres supprimées depuis la date indiquée.
   *
   *
   * @param getOffresSuppr $parameters
   * @return getOffresSupprResponse
   */
  public function getOffresSuppr(getOffresSuppr $parameters) {
    return $this->__soapCall('getOffresSuppr', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le détail des offres créées ou modifiées depuis la
   * date indiquée.
   *
   * @param getDetailBordereauSuppr $parameters
   * @return getDetailBordereauSupprResponse
   */
  public function getDetailBordereauSuppr(getDetailBordereauSuppr $parameters) {
    return $this->__soapCall('getDetailBordereauSuppr', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset qui contient le listing des structures.
   *
   * @param getStructures $parameters
   * @return getStructuresResponse
   */
  public function getStructures(getStructures $parameters) {
    return $this->__soapCall('getStructures', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset.
   *
   * @param getResearch $parameters
   * @return getResearchResponse
   */
  public function getResearch(getResearch $parameters) {
    return $this->__soapCall('getResearch', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset.
   *
   * @param getResearchWithSearch $parameters
   * @return getResearchWithSearchResponse
   */
  public function getResearchWithSearch(getResearchWithSearch $parameters) {
    return $this->__soapCall('getResearchWithSearch', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset.
   *
   * @param getDispo $parameters
   * @return getDispoResponse
   */
  public function getDispo(getDispo $parameters) {
    return $this->__soapCall('getDispo', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

  /**
   * Renvoie un Dataset.
   *
   * @param getDispoBordereau $parameters
   * @return getDispoBordereauResponse
   */
  public function getDispoBordereau(getDispoBordereau $parameters) {
    return $this->__soapCall('getDispoBordereau', array($parameters), array(
        'uri'        => 'http://www.faire-savoir.com/webservices/',
        'soapaction' => ''
      )
    );
  }

}

?>
