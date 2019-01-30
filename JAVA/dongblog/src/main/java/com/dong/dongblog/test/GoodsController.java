package com.dong.dongblog.test;

import org.elasticsearch.index.query.MatchQueryBuilder;
import org.elasticsearch.index.query.QueryBuilders;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.Page;
import org.springframework.data.domain.PageRequest;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;
import java.util.Optional;

@RestController
@RequestMapping("/test")
public class GoodsController {

    @Autowired
    private GoodsRepository goodsRepository;

    @GetMapping("/save")
    public String save() {
        GoodsInfo goodsInfo = new GoodsInfo(System.currentTimeMillis(),
                "商品1" + System.currentTimeMillis(), "苹果");
        goodsRepository.save(goodsInfo);
        goodsInfo = new GoodsInfo(System.currentTimeMillis(),
                "商品2" + System.currentTimeMillis(), "香蕉");
        goodsRepository.save(goodsInfo);
        goodsInfo = new GoodsInfo(System.currentTimeMillis(),
                "商品3" + System.currentTimeMillis(), "苹果和香蕉");
        goodsRepository.save(goodsInfo);
        return "success";
    }

    //http://localhost:8888/delete?id=1525415333329
    @GetMapping("delete")
    public String delete(Long id) {
        goodsRepository.deleteById(id);
        return "success";
    }

    //http://localhost:8888/update?id=1525417362754&name=修改&description=修改
    @GetMapping("update")
    public String update(long id, String name, String description) {
        GoodsInfo goodsInfo = new GoodsInfo(id,
                name, description);
        goodsRepository.save(goodsInfo);
        return "success";
    }

    //http://localhost:8888/getOne?id=1525417362754
    @GetMapping("getOne")
    public GoodsInfo getOne(long id) {
        Optional<GoodsInfo> optional = goodsRepository.findById(id);
        GoodsInfo goodsInfo = optional.get();
        return goodsInfo;
    }


    //每页数量
    private Integer PAGESIZE = 10;

    //http://localhost:8888/getGoodsList?query=商品
    //http://localhost:8888/getGoodsList?query=商品&pageNumber=1
    //根据关键字"商品"去查询列表，name或者description包含的都查询
    @GetMapping("getGoodsList")
    public List<GoodsInfo> getList(Integer pageNumber, String query) {
        if (pageNumber == null){
            pageNumber = 0;
        }
        //es搜索默认第一页页码是0
//        SearchQuery searchQuery = getEntitySearchQuery(pageNumber, PAGESIZE, query);
//        Page<GoodsInfo> goodsPage = goodsRepository.search(searchQuery);
//        return goodsPage.getContent();

        MatchQueryBuilder matchQueryBuilder = QueryBuilders.matchQuery("description", query);
        Page<GoodsInfo> search = goodsRepository.search(matchQueryBuilder, new PageRequest(pageNumber, PAGESIZE));
        return search.getContent();
    }


//    private SearchQuery getEntitySearchQuery(int pageNumber, int pageSize, String searchContent) {
//        FunctionScoreQueryBuilder functionScoreQueryBuilder = QueryBuilders.functionScoreQuery()
//                .add(QueryBuilders.matchPhraseQuery("name", searchContent), ScoreFunctionBuilders.weightFactorFunction(100))
//                .add(QueryBuilders.matchPhraseQuery("description", searchContent), ScoreFunctionBuilders.weightFactorFunction(100))
//                //设置权重分 求和模式
//                .scoreMode("sum")
//                //设置权重分最低分
//                .setMinScore(10);
//
//        // 设置分页
//        Pageable pageable = new PageRequest(pageNumber, pageSize);
//        return new NativeSearchQueryBuilder()
//                .withPageable(pageable)
//                .withQuery(functionScoreQueryBuilder).build();
//    }

}
